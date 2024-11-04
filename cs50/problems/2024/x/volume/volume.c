// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef int16_t SMPL;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

void copy_header(FILE *file_input, FILE *file_output);
void read_sample(FILE *file_input, FILE *file_output, float factor);

int main(int argc, char *argv[]) {
  // Check command-line arguments
  if (argc != 4) {
    printf("Usage: ./volume input.wav output.wav factor\n");
    return 1;
  }

  // Open files and determine scaling factor
  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  FILE *output = fopen(argv[2], "w");
  if (output == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  float factor = atof(argv[3]);

  // TODO: Copy header from input file to output file -- Need testing
  copy_header(input, output);

  // TODO: Read samples from input file and write updated data to output file
  read_sample(input, output, factor);

  // Close files
  fclose(input);
  fclose(output);
}

void copy_header(FILE *file_input, FILE *file_output) {
  // Copy header from input file to output file
  BYTE header[HEADER_SIZE];
  fread(header, HEADER_SIZE, 1, file_input);
  fwrite(header, HEADER_SIZE, 1, file_output);
}

void read_sample(FILE *file_input, FILE *file_output, float factor) {
  SMPL s;
  // Read single sample from input into buffer while there are samples left to
  while (fread(&s, sizeof(SMPL), 1, file_input)) {
    // Update volume of sample
    s *= factor;

    // Write updated sample to new file
    fwrite(&s, sizeof(SMPL), 1, file_output);
  }
}
