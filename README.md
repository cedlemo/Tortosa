#Tortosa

# Project is dead

Tortosa is not maintained anymore. My new vte terminal project is https://github.com/cedlemo/germinal.

## Introduction

Tortosa is a terminal emulator based on the vte3 library. I used gnome-terminal but after different upgrades, some functionalities were removed like background transparency or Japanese input via SCIM.


So I decided to write my own terminal emulator. Even if it looks like a toy, Tortosa does the job of a basic terminal emulator.

+    Tortosa has tabs management

+    Tortosa can remove Window Manager decorations

+    Tortosa works with SCIM

+    Tortosa works with X11 and Weston

+    Tortosa tabs can be themed with a css file

+    Tortosa gets its configuration from a file named tortosarc usually in the directory `~/.config/tortosa` and that's all.

+    Tortosa supports only 2 command lines parameters --config /-c followed by path to the configuration file and --execute -e with the command line to execute.

+    Tortosa configuration and css can be reloaded via a menu or shortcuts. No need to kill/restart it to apply the modifications.

+    Tortosa supports detection of urls/uri and can launch default applications like in gnome-terminal via the main menu. Furthermore Tortosa detect colors pattern and allow you to copy/edit this color via the main menu.

<img src="https://raw.github.com/cedlemo/Tortosa/master/tortosa_overview.png" width="576" height="324" alt="Screenshot">	

*tmux in a tortosa tab. In the top tmux pans, 2 colors schemes scripts displaying terminal color. In the bottom, Tortosa configuration and css file are opened. Just need to save after modifications in the files and use reload functions in the main menu in order to see the modifications applied*
	
##Versions:
Tortosa has a first released version 1.0 which compiles only with the version of the vte3 library prior to 0.34. This version can be built with all the vte library (version >= 2.9) but some functionnalities have been removed:

+    setting vte opacity / transparency
+    setting background image
+    setting background tint color
+    setting background saturation

##Dependencies:
**Note: after the release of vte-3.4, some vte functions that Tortosa uses are deprecated and will not be replaced.**

+    Gtk+ v >= 3.0

+    vte3 v >= 2.9 

+    autotools

+    pkg-config

+   Archlinux:
    > gtk-+3.0
    > vte3

+    Fedora:
    > gtk3-devel
    > vte3-devel

+    Debian: 
    > libvte-2.91-dev

##Installation

```bash
git clone git://github.com/cedlemo/tortosa.git
cd tortosa
./configure
make
```

On a lot of linux distributions, it's recommended to use `./configure --prefix=/usr`
See the INSTALL file for more informations.


##Shortcuts

+    Right clic display main menu

+    ctrl + shift + t create new tab

+    ctrl + shift + right/left arrows allow to navigate trough the tabs.

+    ctrl + shift + c close current tab or close Tortosa if it remains only one tab.

+    ctrl + shift + m display the main menu .

##Configuration

Tortosa can start without a configuration file but that's very ugly.

Create a directory `~/.config/tortosa`. and a file tortosarc in this directory.
This file is a simple key file ( https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html ) with four groups.

+    Window

+    Tabs

+    Vte

+    Css

Here is the tortosarc file that I use:

```
###########################
#main window configuration#
###########################
[Window]
wm_class=Tortosa
wm_name=Tortosa
wm_role=Tortosa
width=1280
height=800
decorated=true
background=#33333355
#background=#92CA5C10
#background=#2a7fff55
#background=rgba(90,90,90,1)
#background=#2E3436dd
```

This part allows user to customize the main window (the GtkWindow). The background color support alpha channel if you system have a running compositing manager. This is done using cairo and can't, normally, be handled by css (https://developer.gnome.org/gtk3/3.0/gtk-question-index.html, see 1.15. How do I create a transparent toplevel window ? ). But I have added parsers for the css so user can use in css:

```
GtkWindow {
	background-color: #000000;
}
```

```
####################
#Tabs configuration#
####################
[Tabs]
show_border=false
show_tabs=true
tabs_position=bottom
#tabs_position=top
#default_tab_name=zsh
#tab_name_max_len=16
active_tab_color=rgba(56,67,230,0.78)
```

The tabs configuration allows to set options for the GtkNotebook widget. Note due to a problem with gtk3 and css parsing it was impossible to set the font color of an active tab label. With Tortosa, user can use the key/value active_tab_color in order to set the font color for the active tab. Furthermore, Tortosa has a css parser that force the font color of the active tab, your css file just need to have:

```
GtkNotebook tab:active {
	...
	color:rgb(26,48,56);
	...
}

Always remember that the css value take precedence on the value in the configuration file event if you only reload the tabs configuration.

```

```
################
#Vte parameters#
################
[Vte]
#command=/bin/zsh -c /usr/bin/tmux
font=Droid Sans Mono 10
foreground=#babdb6
#background=#2E3436f8
background=#222222fa
#black
color0=#111111
#color0=#222222
color8=#555753
#red
color1=#ff6565
color9=#ff8d8d
#green
color2=#93d44f
color10=#c8e7a8
#yellow
color3=#eab93d
color11=#ffc123
#blue
#color4=#204a87
color4=#3465a4
color12=#3465a4
#magenta
color5=#ce5c00
color13=#f57900
#cyan
color6=#89b6e2
color14=#46a4ff
#white
color7=#cccccc
color15=#ffffff
#highlight=#00ff00
cursor_color=#ff0000
cursor_blink=system
#cursor_blink=off
#cursor_blink=on
#cursor_shape=block
cursor_shape=ibeam
#cursor_shape=underline
scrollback_lines=-1
bell_visible=true
bell_audible=false
```

With this part you can set the parameters for the VteTerminal widget. This widget can't handle background transparency anymore. User must provide a full palette color (16 colors) for the moment otherwise the value won't be used.

```
########################################
#Css file to override default gtk theme#
########################################
[Css]
file=/home/cedlemo/.config/tortosa/tortosa.css
```

The file value must be a full path. The css content is applied with the GTK_STYLE_PROVIDER_PRIORITY_USER priority. This means that the current css theme for your system, if you have one, is first loaded and then your css code override this default theme. So it could be useful to reset default theme's css at the beginning of your css file. Here is the global gtk3 organisation of Tortosa:

```
	GtkWindow
	|-------->GtkNotebook
							|---------->GtkLabel
							|---------->VteTerminal	
	GtkMenu
	|-------->GtkMenuItem
	|-------->GtkMenuSeparator
```

see https://developer.gnome.org/gtk3/stable/GtkCssProvider.html for help. Check too https://developer.gnome.org/gtk3/stable/ in each widget related page you can see the style properties part which give informations about css style.

css example:

```css
/*Reset all previous css style*/
*, *:active, *:prelight,*:hover, *:insensitive, *:selected, *:focused, *:inconsistent{
	background: transparent;
	/*background-color: rgba(0,0,0,0);*/
	background-image:none;
	box-shadow: none;
	padding:0px;
	margin:0px;
	border-style:none;
	border-width:0px;
	border-radius:0px;
	border-image:none;
    -GtkWidget-focus-line-width: 0;
		-GtkWidget-focus-padding:0;
		-GtkWidget-interior-focus:false;
	text-shadow:none;
}
.menu {
	background-color: rgba(34,34,34,0.2);
}
.separator{
	-GtkWidget-wide-separators:false;
	-GtkWidget-separator-width: 1;
	-GtkWidget-separator-height: 1;
	background-color:#111111;
}
/**, *:prelight,*:hover, *:insensitive, *:selected, *:focused, *:inconsistent*/
GtkNotebook, .notebook {
	background-color: rgba(46,52,54,0.0);
}
GtkNotebook tab, .notebook tab{
	/*background-color: rgba(46,52,54,0.5);*/
	background-image: -gtk-gradient(linear,
																	center top, 
																	center bottom, 
																	color-stop(0, rgba(0,0,0,0.7)), 
																	color-stop(0.6, rgba(46,52,54,0.5)), 
																	color-stop(1, rgba(46,52,54,0)));
	padding:0px 5px 2px 5px;
	border-radius:0px 0px 0px 0px;
	color:#000000;
}
GtkNotebook tab:active, .notebook tab:active{
	background-image: none;
	padding:2px 7px 2px 7px;
	/*background-color: rgba(46,52,54,0.97);*/
	background-color: rgba(34,34,34,0.93);
	border-style:solid;
	border-color: #eab93d;
	border-width:0px 0px 1px 1px;
	border-radius:0px 0px 6px 0px;
	color:#ffffff;
}
```

