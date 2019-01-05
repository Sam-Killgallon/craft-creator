#include "stdio.h"
#include "crossstitch_image.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must provide a filename!\n");
    printf("\tUsage: %s my_image.jpg\n", argv[0]);
    return 1;
  }

  return crossstitch_image_create(argv[1]);
}
