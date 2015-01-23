#include <gtk/gtk.h>
#include <vte/vte.h>
#include "colors.h"

#ifndef BACKBONE_H
#define	BACKBONE_H
/*window structure handling ref to the widget and customization parameter*/
typedef struct main_window_t
{
		GtkWidget *	widget;
    GtkWidget * entry;
    GtkWidget * vbox;
    GtkWidget * notebook;
		GSList * tabs;
    gboolean transparency;
		struct color_t background;
    gulong key_event_handler_id;
}main_window_t;

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

/*ruby object*/
typedef struct rb_objects
{
  VALUE mRtortosa;
  VALUE cWindow;
  VALUE cFont;
  VALUE cColor;
  VALUE cNotebook;
  VALUE cVte;
  VALUE cWidget;
} rb_objects;
typedef struct  
{
	struct {
		GString *configuration_file;
		GString * command_to_execute;
	} args;
	GdkScreen *screen;
	GdkDisplay *display;
	GtkCssProvider *provider;
	struct main_window_t window;
	struct conf_t configuration;
	guint32 time;
  struct command_t command;
  struct rb_objects rb_objects;
} backbone_t ;

extern backbone_t backbone;
#endif
