#include <vte/vte.h>
#include "backbone.h"
#include "gears.h"
#include "tgregex.h"
#include "dbg.h"
/*Rgexes for vte match*/
#define USERCHARS "-[:alnum:]"
#define USERCHARS_CLASS "[" USERCHARS "]"
#define PASSCHARS_CLASS "[-[:alnum:]\\Q,?;.:/!%$^*&~\"#'\\E]"
#define HOSTCHARS_CLASS "[-[:alnum:]]"
#define HOST HOSTCHARS_CLASS "+(\\." HOSTCHARS_CLASS "+)*"
#define PORT "(?:\\:[[:digit:]]{1,5})?"
#define PATHCHARS_CLASS "[-[:alnum:]\\Q_$.+!*,:;@&=?/~#%\\E]"
#define PATHTERM_CLASS "[^\\Q]'.:}>) \t\r\n,\"\\E]"
#define SCHEME "(?:news:|telnet:|nntp:|file:\\/|https?:|ftps?:|sftp:|webcal:)"
#define USERPASS USERCHARS_CLASS "+(?:" PASSCHARS_CLASS "+)?"
#define URLPATH   "(?:(/"PATHCHARS_CLASS"+(?:[(]"PATHCHARS_CLASS"*[)])*"PATHCHARS_CLASS"*)*"PATHTERM_CLASS")?"
#define HEX_CLASS "[a-fA-F0-9]"
#define UINT8_CLASS "([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])" /*http://www.regular-expressions.info/numericranges.html*/
#define PERCENT_CLASS "(0{0,2}[0-9]\\s*\\%|0?[1-9][0-9]\\s*\\%|100\\s*\\%)"
#define HEX_COLOR "#("HEX_CLASS"{16}|"HEX_CLASS"{12}|"HEX_CLASS"{9}|"HEX_CLASS"{8}|"HEX_CLASS"{6}|"HEX_CLASS"{4}|"HEX_CLASS"{3})"
#define RGB_COLOR "rgb\\s*\\(\\s*"UINT8_CLASS"\\s*\\,\\s*"UINT8_CLASS"\\s*\\,\\s*"UINT8_CLASS"\\s*\\)"
#define RGBPERC_COLOR "rgb\\s*\\(\\s*"PERCENT_CLASS"\\s*\\,\\s*"PERCENT_CLASS"\\s*\\,\\s*"PERCENT_CLASS"\\s*\\)"
#define RGBA_COLOR "rgba\\s*\\(\\s*"UINT8_CLASS"\\s*\\,\\s*"UINT8_CLASS"\\s*\\,\\s*"UINT8_CLASS"\\s*\\,\\s*[0-1](\\.[0-9]*)?\\s*\\)"
#define RGBAPERC_COLOR "rgba\\s*\\(\\s*"PERCENT_CLASS"\\s*\\,\\s*"PERCENT_CLASS"\\s*\\,\\s*"PERCENT_CLASS"\\s*\\,\\s*[0-1](\\.[0-9]*)?\\s*\\)"
static const TerminalRegexPattern url_regex_patterns[] = {
  { SCHEME "//(?:" USERPASS "\\@)?" HOST PORT URLPATH, FLAVOR_AS_IS, G_REGEX_CASELESS },
  { "(?:www|ftp)" HOSTCHARS_CLASS "*\\." HOST PORT URLPATH , FLAVOR_DEFAULT_TO_HTTP, G_REGEX_CASELESS  },
  { "(?:callto:|h323:|sip:)" USERCHARS_CLASS "[" USERCHARS ".]*(?:" PORT "/[a-z0-9]+)?\\@" HOST, FLAVOR_VOIP_CALL, G_REGEX_CASELESS  },
  { "(?:mailto:)?" USERCHARS_CLASS "[" USERCHARS ".]*\\@" HOSTCHARS_CLASS "+\\." HOST, FLAVOR_EMAIL, G_REGEX_CASELESS  },
  { "(?:news:|man:|info:)[[:alnum:]\\Q^_{|}~!\"#$%&'()*+,./;:=?`\\E]+", FLAVOR_AS_IS, G_REGEX_CASELESS  },
	{ HEX_COLOR"|"RGB_COLOR"|"RGBPERC_COLOR"|"RGBA_COLOR"|"RGBAPERC_COLOR, FLAVOR_COLOR, G_REGEX_CASELESS  },
};

GString  *get_flavor_string( int flavor)
{
	GString * flavor_str = NULL;
	switch(flavor)
	{
		case FLAVOR_AS_IS:
			flavor_str = g_string_new("flavor as is");
			break;
		case FLAVOR_DEFAULT_TO_HTTP:
			flavor_str = g_string_new("default to http\n");
			break;
		case FLAVOR_VOIP_CALL:
			flavor_str = g_string_new("flavor voip call\n");
			break;
		case FLAVOR_EMAIL:
			flavor_str = g_string_new("flavor email\n");
			break;
		default :
			flavor_str = NULL;
			break;
	}
	return flavor_str;
}

void precompile_regex(backbone_t * backbone)
{
  /* Precompile the regexes */
  backbone->regexes.number = G_N_ELEMENTS (url_regex_patterns);
  backbone->regexes.g_regexes = g_new0 (GRegex*, backbone->regexes.number);
  backbone->regexes.flavors = g_new0 (TerminalURLFlavour, backbone->regexes.number);
	int i;

  for (i = 0; i < backbone->regexes.number; ++i)
    {
      GError *error = NULL;

      backbone->regexes.g_regexes[i] = g_regex_new (url_regex_patterns[i].pattern,
                                    url_regex_patterns[i].flags | G_REGEX_OPTIMIZE,
                                    0, &error);
      if (error)
        {
          g_message ("%s", error->message);
          g_error_free (error);
        }

      backbone->regexes.flavors[i] = url_regex_patterns[i].flavor;
    }
}

void add_regexes_to_tab(GtkWidget *vte, backbone_t *backbone)
{
	GSList *found = NULL;
	found = g_slist_find_custom(backbone->tabs_data, vte, (GCompareFunc) find_node_by_widget);
	if (found)
	{
		int i;
		for (i = 0; i < backbone->regexes.number; ++i)
    {
      TagData *tag_data;

      tag_data = g_slice_new (TagData);
      tag_data->flavor = backbone->regexes.flavors[i];
      tag_data->tag = vte_terminal_match_add_gregex (VTE_TERMINAL(vte), backbone->regexes.g_regexes[i], 0);
      //vte_terminal_match_set_cursor_type (terminal, tag_data->tag, URL_MATCH_CURSOR);		
			((tab_data_t *) found)->match_tags = g_slist_prepend( ( (tab_data_t *) found )->match_tags, tag_data);
		}
	}
	else
		LOG_WARN("vte not found in tabs_data GSList\n");
}

gchar * get_regex_match_for_tab_on_button_press(GtkWidget *vte, GdkEventButton *event, int * flavor, backbone_t * backbone)
{
	int cell_width_pixels, cell_height_pixels, row, col;
	GtkBorder *inner_border = NULL;
	cell_width_pixels = vte_terminal_get_char_width (VTE_TERMINAL(vte));
	cell_height_pixels = vte_terminal_get_char_height (VTE_TERMINAL(vte));
	gtk_widget_style_get (vte, "inner-border", &inner_border, NULL);
	col = (event->x - (inner_border ? inner_border->left : 0)) / cell_width_pixels;
	row = (event->y - (inner_border ? inner_border->top : 0)) / cell_height_pixels;
	gtk_border_free (inner_border);

	gchar *match =NULL;
	GSList *tags;
	int tag;

	match = vte_terminal_match_check (VTE_TERMINAL (vte), col, row, &tag);
	GSList *found = NULL;
	found = g_slist_find_custom(backbone->tabs_data, vte, (GCompareFunc) find_node_by_widget);

	if(!found)
		return NULL;
	
	if(match)	
	{
		for (tags = ((tab_data_t *) found->data)->match_tags; tags != NULL; tags = tags->next)
		{
			TagData *tag_data = (TagData*) tags->data;
			if (tag_data->tag == tag)
			{
	      if (flavor)
	        *flavor = tag_data->flavor;
	       return match;
			}
		}
		g_free (match);
		return NULL;
	}
	else
		return NULL;
}

/*Regexes for css match*/
void compile_css_regexes(backbone_t * backbone)
{
#define GTKWINDOW_CSS_KEY "(GtkWindow|.window)"
#define GTKNOTEBOOK_TAB_ACTIVE_KEY "(GtkNotebook\\s+tab\\s*\\:\\s*active|.notebook\\s+tab\\s*\\:\\s*active)"
	const gchar window_background_color_pattern[]="\\s*"GTKWINDOW_CSS_KEY"[^\\{]*\\{[^\\{]*\\;*\\s*background-color\\s*\\:\\s*("HEX_COLOR"|"RGB_COLOR"|"RGBPERC_COLOR"|"RGBA_COLOR"|"RGBAPERC_COLOR")\\s*\\;[^\\{]*\\}";
	const gchar notebook_tab_active_color_pattern[]="\\s*"GTKNOTEBOOK_TAB_ACTIVE_KEY"\\s*[^\\{]*\\{[^\\{]*\\;\\s*color\\s*\\:\\s*("HEX_COLOR"|"RGB_COLOR"|"RGBPERC_COLOR"|"RGBA_COLOR"|"RGBAPERC_COLOR")\\s*\\;[^\\{]*\\}";
	backbone->css.window_background_color_regex = g_regex_new(window_background_color_pattern, /*GRegexCompileFlags compile_options*/ G_REGEX_OPTIMIZE, /*GRegexMatchFlags match_options*/ 0, /* GError **error*/ NULL);
	backbone->css.notebook_tab_active_color_regex = g_regex_new( notebook_tab_active_color_pattern, G_REGEX_OPTIMIZE, 0, NULL);
}

GString * get_css_regex_match(GRegex *regex, const gchar *string)
{
	GMatchInfo *match_info;
	gboolean  have_matches;
	gchar *match =NULL;
	have_matches = g_regex_match (regex, string, 0, &match_info);
  while (g_match_info_matches (match_info))
	{
	  if (match)
		{
			g_free(match);
			match = NULL;
		}
		match = g_match_info_fetch (match_info, 2);
	  
	  g_match_info_next (match_info, NULL);
	}

	g_match_info_free (match_info);

	GString * color = NULL;
	
	if (match)
	{
		color = g_string_new(match);
		g_free(match);
	}
	return color;
}

void free_css_regexes(backbone_t *backbone)
{
	g_regex_unref(backbone->css.window_background_color_regex);
}
