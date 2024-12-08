#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]) {
  /* TODO:
   * check the first 4 bytes in a buffer -- done
   */
  // Accept a single command-line argument
  if (argc != 2) {
    printf("Usage: ./recover FILE\n");
    return 1;
  }

  // Open the memory card
  FILE *card = fopen(argv[1], "r");

  // Create a buffer for a block of data
  BYTE buffer[512];

  // Create a file name
  char *filename = malloc(sizeof(BYTE) * 8);
  if (filename == NULL) {
    return 1;
  }

  filename[7] = '\0';

  // Count JPEGs
  int counter = 0;

  bool firstImage = false;
  bool imageOpened = false;
  FILE *img;
  // While there's still data left to read from the memory card
  while (fread(buffer, 1, 512, card) == 512) {
    // Check if there is a JPEG header
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0) {
      imageOpened = true;

      // Check if it is the first JPEG
      if (!firstImage) {
        firstImage = true;
      } else {
        // close the previous image
        fclose(img);
      }

      sprintf(filename, "%03i.jpg", counter);
      counter++;

      img = fopen(filename, "w");
      if (img == NULL) {
        return 2;
      }

      // write data to the image
      fwrite(buffer, 1, 512, img);

    } else if (imageOpened) {
      // write data to the image if there is a file opened
      fwrite(buffer, 1, 512, img);
    }
  }

  free(filename);
  if (img != NULL) {
    fclose(img);
  }
  fclose(card);
}
