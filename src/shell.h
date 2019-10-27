#ifndef TORTOSA_SHELL_H
#define TORTOSA_SHELL_H
#include <glib-object.h>
#include <stdio.h>

G_BEGIN_DECLS

#define TORTOSA_TYPE_SHELL tortosa_shell_get_type ()
G_DECLARE_FINAL_TYPE( TortosaShell, tortosa_shell, TORTOSA, SHELL, GObject)

TortosaShell *tortosa_shell_get_default (void);
G_END_DECLS
#endif /* !TORTOSA_SHELL_H */
