#include "terminal.h"

void
spawn_async_cb (VteTerminal *terminal,
                GPid pid,
                GError *error,
                gpointer user_data)
{

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
