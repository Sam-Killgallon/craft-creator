#include "stdio.h"
#include <math.h>
#include <float.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "crossstitch_image.h"

int crossstitch_image_create(char *filename) {
  GdkPixbuf *pixbuf = NULL;
  GError *error = NULL;
  // display_file_info(filename);

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

  // for (int i = 0 ; i < (300 * rowstride) ; i += number_of_channels) {
  // int offset = (500 * rowstride);
  for (int i = 0 ; i < (height * rowstride) ; i += number_of_channels) {
    int *colour = new_colour(pixels[i], pixels[i + 1], pixels[i + 2]);
    // printf("Starting colour: %i %i %i, ", pixels[i], pixels[i + 1], pixels[i + 2]);
    // printf("Closest colour: %i %i %i\n", colour[0], colour[1], colour[2]);
    pixels[i]     = colour[0];   // Red
    pixels[i + 1] = colour[1];   // Green
    pixels[i + 2] = colour[2];   // Blue
  }
}

static int *new_colour(int r, int g, int b) {
  int *closest_colour;
  double closest_score = DBL_MAX;
  // printf("Finding match for %i %i %i\n", r, g, b);

  for (int i = 0; i < 27; ++i) {
    int *colour = valid_colours()[i];
    int r_diff = difference(r, colour[0]);
    int g_diff = difference(g, colour[1]);
    int b_diff = difference(b, colour[2]);

    double score = sqrt((r_diff * r_diff) + (g_diff * g_diff) + (b_diff * b_diff));
    // printf("Score: %lf - %i %i %i\n", score, colour[0], colour[1], colour[2]);
    if (score < closest_score) {
      // printf("New closer colour %i %i %i with score %lf\n", colour[0], colour[1], colour[2], score);
      closest_score = score;
      closest_colour = colour;
    }
  }

  return closest_colour;
  // return valid_colours()[1];
}

static int difference(int a, int b) {
  if (a > b) {
    return a - b;
  } else {
    return b - a;
  }
}

// static int (*valid_colours(void))[3] {
//   static int colours[16][3] = {
//     { 0, 255, 255 },
//     { 0, 0, 0 },
//     { 0, 0, 255 },
//     { 255, 0, 255 },
//     { 128, 128, 128 },
//     { 0, 128, 0 },
//     { 0, 255, 0 },
//     { 128, 0, 0 },
//     { 0, 0, 128 },
//     { 128, 128, 0 },
//     { 128, 0, 128 },
//     { 255, 0, 0 },
//     { 192, 192, 192 },
//     { 0, 128, 128 },
//     { 255, 255, 255 },
//     { 255, 255, 0 },
//   };

//   return colours;
// }

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
// COLOURS = [
//   [0, 0, 0],
//   [55, 55, 55],
//   [128, 128, 128],
//   [200, 200, 200],
//   [255, 255, 255],
// ]

// def distance(pixel, colour)
//   r = (pixel[0] - colour[0]) ** 2
//   g = (pixel[1] - colour[1]) ** 2
//   b = (pixel[2] - colour[2]) ** 2

//   Math.sqrt(r + g + b)
// end

// COLOURS.min_by { |colour| distance([160, 170, 170], colour) }


static int (*valid_colours(void))[3] {
  static int colours[27][3] = {
{ 0, 0, 0 },
{ 0, 0, 127 },
{ 0, 0, 254 },
{ 0, 127, 0 },
{ 0, 127, 127 },
{ 0, 127, 254 },
{ 0, 254, 0 },
{ 0, 254, 127 },
{ 0, 254, 254 },
{ 127, 0, 0 },
{ 127, 0, 127 },
{ 127, 0, 254 },
{ 127, 127, 0 },
{ 127, 127, 127 },
{ 127, 127, 254 },
{ 127, 254, 0 },
{ 127, 254, 127 },
{ 127, 254, 254 },
{ 254, 0, 0 },
{ 254, 0, 127 },
{ 254, 0, 254 },
{ 254, 127, 0 },
{ 254, 127, 127 },
{ 254, 127, 254 },
{ 254, 254, 0 },
{ 254, 254, 127 },
{ 254, 254, 254 }

  };
  return colours;
}
