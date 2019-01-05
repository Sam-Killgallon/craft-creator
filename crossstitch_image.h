# pragma once
#include <gdk-pixbuf/gdk-pixbuf.h>

int crossstitch_image_create(char *filename);
// static int **valid_colours();
static int (*valid_colours(void))[3];
static int *new_colour(int r, int g, int b);
static void adjust_colours(GdkPixbuf *pixbuf);
static void display_file_info(char *filename);
static int difference(int a, int b);
