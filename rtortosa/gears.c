#include <stdlib.h>
#include <vte/vte.h>
#include "gears.h"
#include "backbone.h"
#include "colors.h"
#include "dbg.h"

void free_backbone( backbone_t * backbone)
{
	FREE_GSTRING(backbone->window.background.color);
  FREE_GSTRING(backbone->command.line);	
}

void quit_gracefully(backbone_t * backbone)
{
	free_backbone(backbone);
  gtk_main_quit();
}
void widget_set_transparent_background(GtkWidget *widget)
{
  GdkRGBA transparent;
  transparent.red =0;
  transparent.green = 0;
  transparent.blue = 0;
  transparent.alpha = 0;
  gtk_widget_override_background_color(widget,GTK_STATE_FLAG_NORMAL,&transparent);

}
//Casts
uint32_t uint2uint32(unsigned int a){
  return a > UINT32_MAX ? UINT32_MAX : a;
};
uint16_t uint2uint16(unsigned int a){
  return a > UINT16_MAX ? UINT16_MAX : a;
};
uint8_t uint2uint8(unsigned int a){
  return a > UINT8_MAX ? UINT8_MAX : a;
};
int32_t int2int32( int a){
  if (a >= 0)
  {
    return a > INT32_MAX ? INT32_MAX : a;
  }
  else
  {
    return a < INT32_MIN ? INT32_MIN : a;
  }
};
int16_t int2int16( int a){
  if (a >= 0)
  {
    return a > INT16_MAX ? INT16_MAX : a;
  }
  else
  {
    return a < INT16_MIN ? INT16_MIN : a;
  }
};
int8_t int2int8( int a){
  if (a >= 0)
  {
    return a > INT8_MAX ? INT8_MAX : a;
  }
  else
  {
    return a < INT8_MIN ? INT8_MIN : a;
  }
};

