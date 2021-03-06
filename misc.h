//      misc.h - miscellaneous functions for lualock
//      Copyright ©2011 Guff <cassmacguff@gmail.com>
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//

#ifndef MISC_H
#define MISC_H

#include <gdk/gdk.h>

#include "lualock.h"

cairo_surface_t* create_surface(gint width, gint height);

layer_t* create_layer(gint width, gint height);
void add_layer(layer_t *layer);
void remove_layer(layer_t *layer);
void replace_layer(layer_t *old_layer, layer_t *new_layer);
void layer_destroy(layer_t *layer);

void parse_color(const gchar *hex, gdouble *r, gdouble *g, gdouble *b, gdouble *a);

char* get_password_mask();

void get_abs_pos(double rel_x, double rel_y, double *x, double *y);
void get_abs_pos_for_dims(double dim_w, double dim_h, double rel_w, double rel_h,
                          double *w, double *h);

void add_timer(guint id);
void remove_timer(guint id);
void clear_timers();

void register_update(gdouble x, gdouble y, gdouble w, gdouble h);
void register_update_for_layer(layer_t *layer);
void clear_updates();
void update_screen();

#endif
