#include "stdio.h"
#include <math.h>
#include <float.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "crossstitch_image.h"

#define NUMBER_OF_COLOURS 64

int crossstitch_image_create(char *filename) {
  GdkPixbuf *pixbuf = NULL;
  GError *error = NULL;

  pixbuf = gdk_pixbuf_new_from_file_at_size(filename, 1000, 1000, &error);
  if (!pixbuf) {
    printf("%s\n", error->message);
    return error->code;
  }

  adjust_colours(pixbuf);

  gboolean success = gdk_pixbuf_save(pixbuf, "output.jpg", "jpeg", &error, NULL);
  if (!success) {
    printf("%s\n", error->message);
    return error->code;
  }

  return 0;
}

static void adjust_colours(GdkPixbuf *pixbuf) {
  int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
  int number_of_channels = gdk_pixbuf_get_n_channels(pixbuf);
  int height = gdk_pixbuf_get_height(pixbuf);
  g_assert(number_of_channels == 3);

  guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

  for (int i = 0 ; i < (height * rowstride) ; i += number_of_channels) {
    int *colour = new_colour(pixels[i], pixels[i + 1], pixels[i + 2]);
    pixels[i]     = colour[0];   // Red
    pixels[i + 1] = colour[1];   // Green
    pixels[i + 2] = colour[2];   // Blue
  }
}

static int *new_colour(int r, int g, int b) {
  int *closest_colour;
  double closest_score = DBL_MAX;

  for (int i = 0; i < NUMBER_OF_COLOURS; ++i) {
    int *colour = valid_colours()[i];
    int r_diff = difference(r, colour[0]);
    int g_diff = difference(g, colour[1]);
    int b_diff = difference(b, colour[2]);

    double score = sqrt((r_diff * r_diff) + (g_diff * g_diff) + (b_diff * b_diff));
    if (score < closest_score) {
      closest_score = score;
      closest_colour = colour;
    }
  }

  return closest_colour;
}

static int difference(int a, int b) {
  if (a > b) {
    return a - b;
  } else {
    return b - a;
  }
}

static void display_file_info(char *filename) {
  GdkPixbufFormat *format;
  gint *width = malloc(sizeof(gint));
  gint *height = malloc(sizeof(gint));

  format  = gdk_pixbuf_get_file_info(filename, width, height);
  printf("'%s' - Type: %s, Size: %ix%i\n", filename, gdk_pixbuf_format_get_name(format), *width, *height);

  free(width);
  free(height);
}

/*
Go through each pixel and find the closest official colour to it, then convert it that colour

Distance between 2 points in 3d space
d = ((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)^1/2
sqrt of the sum of their squared differences
*/

static int (*valid_colours(void))[3] {
  static int colours[NUMBER_OF_COLOURS][3] = {
    { 0, 0, 0 },
    { 0, 0, 70 },
    { 0, 0, 140 },
    { 0, 0, 210 },
    { 0, 70, 0 },
    { 0, 70, 70 },
    { 0, 70, 140 },
    { 0, 70, 210 },
    { 0, 140, 0 },
    { 0, 140, 70 },
    { 0, 140, 140 },
    { 0, 140, 210 },
    { 0, 210, 0 },
    { 0, 210, 70 },
    { 0, 210, 140 },
    { 0, 210, 210 },
    { 70, 0, 0 },
    { 70, 0, 70 },
    { 70, 0, 140 },
    { 70, 0, 210 },
    { 70, 70, 0 },
    { 70, 70, 70 },
    { 70, 70, 140 },
    { 70, 70, 210 },
    { 70, 140, 0 },
    { 70, 140, 70 },
    { 70, 140, 140 },
    { 70, 140, 210 },
    { 70, 210, 0 },
    { 70, 210, 70 },
    { 70, 210, 140 },
    { 70, 210, 210 },
    { 140, 0, 0 },
    { 140, 0, 70 },
    { 140, 0, 140 },
    { 140, 0, 210 },
    { 140, 70, 0 },
    { 140, 70, 70 },
    { 140, 70, 140 },
    { 140, 70, 210 },
    { 140, 140, 0 },
    { 140, 140, 70 },
    { 140, 140, 140 },
    { 140, 140, 210 },
    { 140, 210, 0 },
    { 140, 210, 70 },
    { 140, 210, 140 },
    { 140, 210, 210 },
    { 210, 0, 0 },
    { 210, 0, 70 },
    { 210, 0, 140 },
    { 210, 0, 210 },
    { 210, 70, 0 },
    { 210, 70, 70 },
    { 210, 70, 140 },
    { 210, 70, 210 },
    { 210, 140, 0 },
    { 210, 140, 70 },
    { 210, 140, 140 },
    { 210, 140, 210 },
    { 210, 210, 0 },
    { 210, 210, 70 },
    { 210, 210, 140 },
    { 210, 210, 210 }
  };
  return colours;
}
