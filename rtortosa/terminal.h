#ifndef TERMINAL_H
#define TERMINAL_H
#include <gtk/gtk.h>
#include <vte/vte.h>
#include "backbone.h"
#include <ruby.h>
void new_terminal_emulator(backbone_t *backbone);
#endif //TERMINAL_H
