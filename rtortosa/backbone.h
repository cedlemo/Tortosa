#include <gtk/gtk.h>
#include <vte/vte.h>
#include "colors.h"

#ifndef BACKBONE_H
#define	BACKBONE_H
/*window structure handling ref to the widget and customization parameter*/
typedef struct window_t
{
		GtkWidget *	widget;
    GtkWidget * entry;
    GtkWidget * vbox;
    GtkWidget * notebook;
		gboolean transparency;
		struct color_t background;
}window_t;

/*configuration file path*/
typedef struct conf_t
{
	GString * dir_path;
	GString * file_path;
	GKeyFile * keyfile;
}conf_t;

/*Command mode helper*/
typedef struct command_t
{
  GString * line;
  gboolean mode;
} command_t;

typedef struct  
{
	struct {
		GString *configuration_file;
		GString * command_to_execute;
	} args;
	GdkScreen *screen;
	GdkDisplay *display;
	GtkCssProvider *provider;
	struct window_t window;
	struct conf_t configuration;
	guint32 time;
  struct command_t command;
} backbone_t ;

extern backbone_t backbone;
#endif
