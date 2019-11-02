#include "shell.h"

struct _TortosaShell {
    GObject parent_instance;
};

static TortosaShell * tortosa_shell = NULL;

G_DEFINE_TYPE (TortosaShell, tortosa_shell, G_TYPE_OBJECT)

static void
tortosa_shell_dispose (GObject *gobject)
{
    G_OBJECT_CLASS (tortosa_shell_parent_class)->dispose (gobject);
}

static void
tortosa_shell_finalize (GObject *gobject)
{
    G_OBJECT_CLASS (tortosa_shell_parent_class)->finalize (gobject);
}

/**
 * Tortosa shell Class init (called only once)
 * */
static void
tortosa_shell_class_init (TortosaShellClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    object_class->finalize = tortosa_shell_finalize;
    object_class->dispose = tortosa_shell_dispose;
}

/**
 * Tortosa shell Instance init (called each time g_object_new is
 * called with TORTOSA_TYPE_SHELL)
 * */
static void
tortosa_shell_init (TortosaShell *self)
{
}

static TortosaShell *
tortosa_shell_new ()
{
    return g_object_new (TORTOSA_SHELL_TYPE, NULL);
}

TortosaShell *
tortosa_shell_get_default ()
{
    if (tortosa_shell == NULL)
        tortosa_shell = tortosa_shell_new ();

    return tortosa_shell;
}
