#ifndef BACKBONE_H
#define	BACKBONE_H
#include <gtk/gtk.h>
#include <vte/vte.h>
#include "colors.h"
/*window structure handling ref to the widget and customization parameter*/
typedef struct window_t
{
		GtkWidget *	widget;
		GString * title;
		GString * wm_class;
		GString * wm_name;
		GString * role;
		gint width;
		gint height;
		gboolean decorated;
		gboolean transparency;
		struct color_t background;
}window_t;

/*notebook structure handling ref to the widget and customization parameter*/
typedef struct notebook_t
{
		GtkWidget *	widget;
		gboolean show_border;
		gboolean show_tabs;
		GtkPositionType tabs_position;
		GString * default_tab_name;
		gint tab_name_max_len;
}notebook_t;

/*vte structure handling general configuration for all the launched vte*/
typedef struct vte_t
{
		GString * command;
		struct color_t foreground;
		struct color_t background;
		struct color_t palette[16];
	  gboolean user_valid_palette;
		guint16 opacity;
		GString * background_image;
		gdouble background_saturation;
		GString * background_tint_color;
		GdkColor background_tint;
		glong scrollback_lines;
		GString * font;
		struct color_t highlight;
		struct color_t cursor_color;
		VteTerminalCursorBlinkMode cursor_blink;
		VteTerminalCursorShape cursor_shape;
		gboolean bell_visible;
		gboolean bell_audible;
}vte_t;

/*css file information*/
typedef struct css_t
{
		GString * path;
		GFile * file;
}css_t;

/*configuration file path*/
typedef struct conf_t
{
	GString * dir_path;
	GString * file_path;
	GKeyFile * keyfile;
}conf_t;

/*tabs info data node*/
typedef struct tab_data_t {
	GtkWidget * widget;
	GPid pid;
} tab_data_t;

typedef struct  
{
	GdkScreen *screen;
	GdkDisplay *display;
	GtkCssProvider *provider;
	GSList * tabs_data;
	struct window_t window;
	struct notebook_t notebook;
	struct vte_t vte;
	GtkWidget * main_menu;
	GtkWidget * resize_menu;
	GtkWidget * reload_menu;
	struct css_t css;
	struct conf_t configuration;
	guint32 time;
	struct {
		gboolean withdrawn;
		gboolean iconified;
		gboolean maximized;
		gboolean sticky;
		gboolean fullscreen;
		gboolean above;
		gboolean below;
	} state;
} backbone_t ;

#endif
