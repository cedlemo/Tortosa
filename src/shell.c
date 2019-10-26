#include "shell.h"

struct _TortosaShell {
    GObject parent_instance;
};

static TortosaShell * tortosa_shell = NULL;

G_DEFINE_TYPE (TortosaShell, tortosa_shell, G_TYPE_OBJECT)

static void
tortosa_shell_class_init (TortosaShellClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    object_class->constructed = tortosa_shell_constructed;
}

static void
tortosa_shell_init (TortosaShell *self)
{

}
