#include "preferences.h"

struct _TortosaPreferences {
    GtkDialog parent;
};

typedef struct _TortosaPreferencesPrivate TortosaPreferencesPrivate;

struct _TortosaPreferencesPrivate {
    GSettings *settings;
    GtkWidget *font;
};

G_DEFINE_TYPE_WITH_PRIVATE(TortosaPreferences, tortosa_preferences, GTK_TYPE_DIALOG)

static void
tortosa_preferences_init (TortosaPreferences *prefs)
{
    TortosaPreferencesPrivate *priv;
    priv = tortosa_preferences_get_instance_private (prefs);
    gtk_widget_init_template (GTK_WIDGET (prefs));
    priv->settings = g_settings_new ("com.github.cedlemo.tortosa");
    g_settings_bind (priv->settings, "font",
                     priv->font, "font",
                     G_SETTINGS_BIND_DEFAULT);
}

static void
tortosa_preferences_dispose (GObject *object)
{
    TortosaPreferencesPrivate *priv;
    priv = tortosa_preferences_get_instance_private (TORTOSA_PREFERENCES (object));
    g_clear_object (&priv->settings);
    G_OBJECT_CLASS (tortosa_preferences_parent_class)->dispose (object);
}

static void
tortosa_preferences_class_init (TortosaPreferencesClass *class)
{
    G_OBJECT_CLASS (class)->dispose = tortosa_preferences_dispose;
    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
            "/org/gtk/exampleapp/prefs.ui");
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), TortosaPreferences, font);
}

TortosaPreferences *
tortosa_preferences_new (TortosaWindow *win)
{
    return g_object_new (TORTOSA_PREFERENCES_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
