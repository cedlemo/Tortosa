/*
 * Copyright 2019-2020 Cedric LE MOIGNE, cedlemo@gmx.com
 * This file is part of Tortosa Terminal Emulator.
 *
 * Tortosa is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Tortosa is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tortosa.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "terminal.h"
#include "shell.h"

struct _TortosaTerminal {
    VteTerminal parent_instance;
    GtkPopover *termmenu;
};


G_DEFINE_TYPE(TortosaTerminal, tortosa_terminal, VTE_TYPE_TERMINAL)

void
child_exited_cb (VteTerminal *terminal,
                 gint status)
{
    TortosaNotebook *notebook = tortosa_shell_get_notebook ();
    int remaining_terminals = tortosa_notebook_close_terminal (notebook, TORTOSA_TERMINAL (terminal));

    if(remaining_terminals == 0) {

        g_message("Last terminal closed, bye!");

        gtk_window_close (GTK_WINDOW (tortosa_shell_get_window ()));
    }
}

const char *colors[PALETTE_SIZE] = {
    COLOR0, COLOR1, COLOR2, COLOR3, COLOR4, COLOR5, COLOR6, COLOR7, COLOR8, COLOR9, COLOR10, COLOR11, COLOR12, COLOR13, COLOR14, COLOR15
};

static gboolean
font_string_to_font_desc (GValue   *value,
                          GVariant *variant,
                          gpointer  user_data)
{
  const char *str = NULL;

  // get a pointer out of the variant, instead of copying the string out
  g_variant_get (variant, "&s", &str);

  // empty strings are invalid
  if (str == NULL || *str == '\0')
    return FALSE;

  // create a new PangoFontDescription from the font description string
  PangoFontDescription *font_desc = pango_font_description_from_string (str);

  if (font_desc == NULL)
    return FALSE;

  // PangoFontDescription is a boxed GType, so we use the appropriate setter
  // for GValue; we want the GValue to take ownership of the newly created
  // font description instance, since we don't care about it any more
  g_value_take_boxed (value, font_desc);

  // conversion successful
  return TRUE;
}

static void
show_termmenu (GtkWidget *terminal, GdkEventButton *event) {
    GtkPopover *popover = tortosa_shell_get_termmenu ();
    gdouble parent_x, parent_y;
    GtkAllocation allocation;

    gdk_window_coords_to_parent (event->window, event->x, event->y, &parent_x, &parent_y);
    gtk_popover_set_relative_to (popover, GTK_WIDGET (terminal));
    gtk_widget_get_allocation (GTK_WIDGET (terminal), &allocation);
    GdkRectangle rect = {
        .x = parent_x - allocation.x,
        .y = parent_y - allocation.y,
        .width = 1,
        .height = 1
    };

    gtk_popover_set_pointing_to (popover, &rect);

    gtk_widget_show (GTK_WIDGET (popover));
}

static gboolean
handle_button_press_event (GtkWidget *terminal,
                           GdkEvent  *event,
                           gpointer data)
{
   if (event->type == GDK_BUTTON_PRESS)
   {
       GdkEventButton *event_button = (GdkEventButton *) event;
       if(event_button->button == GDK_BUTTON_SECONDARY)
       {
           show_termmenu (terminal, event_button);
           return TRUE;
       }
   }
   return FALSE;
}

static void
handle_window_title_changed (GtkWidget *terminal,
                             gpointer data)
{
    GtkLabel *term_title = tortosa_shell_get_term_title ();
    TortosaNotebook *notebook = tortosa_shell_get_notebook ();
    TortosaTerminal *current = tortosa_notebook_get_current_terminal (notebook);
    if(GTK_WIDGET (current) == terminal)
        gtk_label_set_text (term_title, vte_terminal_get_window_title (VTE_TERMINAL (terminal)));
}

void
spawn_async_cb (VteTerminal *terminal,
                GPid pid,
                GError *error,
                gpointer user_data)
{
    GdkRGBA palette[PALETTE_SIZE];
    GSettings *settings = tortosa_shell_get_settings ();

    for (int i = 0; i < PALETTE_SIZE; i++)
    {
        gdk_rgba_parse (&palette[i], colors[i]);
    }

    GdkRGBA foreground;
    GdkRGBA background;
    gdk_rgba_parse (&foreground, FOREGROUND);
    gdk_rgba_parse (&background, BACKGROUND);

    vte_terminal_set_colors (terminal,
                             &foreground,         // const GdkRGBA *foreground,
                             &background,         // const GdkRGBA *background,
                             (GdkRGBA *) palette, // const GdkRGBA *palette,
                             PALETTE_SIZE         // gsize palette_size
                            );
    vte_terminal_set_allow_bold (terminal, TRUE);
    vte_terminal_set_scroll_on_output (terminal, TRUE);
    vte_terminal_set_scrollback_lines (terminal, -1);

    g_settings_bind_with_mapping (settings, "font",
                                  terminal, "font-desc",
                                  G_SETTINGS_BIND_GET,
                                  font_string_to_font_desc, NULL, NULL, NULL);

    g_signal_connect (terminal, "button-press-event", G_CALLBACK (handle_button_press_event), NULL);
    g_signal_connect (terminal, "window-title-changed", G_CALLBACK (handle_window_title_changed), NULL);
}


static void
tortosa_terminal_class_init (TortosaTerminalClass *klass)
{
    VTE_TERMINAL_CLASS (klass)->child_exited = child_exited_cb;
}

static void
tortosa_terminal_init (TortosaTerminal *terminal)
{
    gchar **argvp=0;
	int argc;

    if ( g_shell_parse_argv("/bin/zsh", &argc, &argvp,0) != TRUE )
    {
        g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
    }

    GError *error = NULL;

	vte_terminal_spawn_async (VTE_TERMINAL (terminal),
                                   VTE_PTY_DEFAULT,
								   NULL,                // working_directory
                                   argvp,               // char **argv
								   NULL,                // char **envv
								   G_SPAWN_SEARCH_PATH,
								   NULL,                // GSpawnChildSetupFunc child_setup,
								   NULL,                // gpointer child_setup_data
                                   NULL,                // GDestroyNotify child_setup_data_destroy
                                   1000,                // a timeout value in ms, or -1 to wait indefinitely
								   NULL,                // cancellable a GCancellable, or NULL.
								   spawn_async_cb,
                                   NULL);

//	{
//		LOG_ERR("%s\n", error->message);
//		g_strfreev(argvp);
//		/*TODO make a clean exit*/
//		exit(EXIT_FAILURE);
//	}
	g_strfreev(argvp);
}

TortosaTerminal *
tortosa_terminal_new (void)
{
    return g_object_new (TORTOSA_TERMINAL_TYPE, NULL);
}

void
tortosa_terminal_copy_selection (TortosaTerminal *terminal)
{
    vte_terminal_copy_clipboard_format (VTE_TERMINAL (terminal), VTE_FORMAT_TEXT);
}

void
tortosa_terminal_paste_selection (TortosaTerminal *terminal)
{
    vte_terminal_paste_clipboard (VTE_TERMINAL (terminal));
}
