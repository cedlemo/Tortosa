/*
 * Copyright 2019 Cedric LE MOIGNE, cedlemo@gmx.com
 * This file is part of Tortosa Terminal Emulator.
 *
 * Tortosa is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Tortosa is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tortosa.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TORTOSA_TERMINAL_H
#define TORTOSA_TERMINAL_H
#include <stdlib.h>
#include <gtk/gtk.h>
#include <vte/vte.h>
#include "dbg.h"

#define FOREGROUND "#ebdbb2"
#define BACKGROUND "#282828"
#define COLOR0 "#282828"
#define COLOR1 "#cc241d"
#define COLOR2 "#98971a"
#define COLOR3 "#d79921"
#define COLOR4 "#458588"
#define COLOR5 "#b16286"
#define COLOR6 "#689d6a"
#define COLOR7 "#a89984"
#define COLOR8 "#928374"
#define COLOR9 "#fb4934"
#define COLOR10 "#b8bb26"
#define COLOR11 "#fabd2f"
#define COLOR12 "#83a598"
#define COLOR13 "#d3869b"
#define COLOR14 "#8ec07c"
#define COLOR15 "#ebdbb2"
#define PALETTE_SIZE 16

G_BEGIN_DECLS

#define TORTOSA_TERMINAL_TYPE (tortosa_terminal_get_type ())
G_DECLARE_FINAL_TYPE(TortosaTerminal, tortosa_terminal, TORTOSA, TERMINAL, VteTerminal)

TortosaTerminal * tortosa_terminal_new (void);

G_END_DECLS
#endif /* !TORTOSA_TERMINAL_H */
