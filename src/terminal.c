#include "terminal.h"

const char *colors[PALETTE_SIZE] = {
    BACKGROUND, COLOR0, COLOR1, COLOR2, COLOR3, COLOR4, COLOR5, FOREGROUND,
    COLOR6, COLOR7, COLOR8, COLOR9, COLOR10, COLOR11, COLOR12, COLOR13, COLOR14, COLOR15
};


void
spawn_async_cb (VteTerminal *terminal,
                GPid pid,
                GError *error,
                gpointer user_data)
{
    GdkRGBA palette[PALETTE_SIZE];

    for (int i = 0; i < PALETTE_SIZE; i++)
    {
        gdk_rgba_parse(&palette[i], colors[i]);
    }

    vte_terminal_set_colors (terminal,
                             NULL,                // const GdkRGBA *foreground,
                             NULL,                // const GdkRGBA *background,
                             (GdkRGBA *) palette, // const GdkRGBA *palette,
                             16                   // gsize palette_size
                            );
}

GtkWidget * tortosa_terminal_new (void)
{
    GtkWidget *vte;
    gchar **argvp=0;
	int argc;

    if ( g_shell_parse_argv("/bin/zsh", &argc, &argvp,0) != TRUE )
    {
        g_shell_parse_argv(g_getenv("SHELL"), &argc, &argvp,0);
    }

    GError *error = NULL;
    vte = vte_terminal_new();

	vte_terminal_spawn_async (VTE_TERMINAL(vte),
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
//	g_strfreev(argvp);

    return vte;
}