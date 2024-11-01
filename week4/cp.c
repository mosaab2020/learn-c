#include <stdint.h>
#include <stdio.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]) {
  FILE *src = fopen(argv[1], "rb");
  FILE *dst = fopen(argv[2], "wb");
  if (src == NULL || dst == NULL) {
    return 1;
  }

  BYTE b;

  // fread(is where to load those bytes in memory, what is the size, how many
  // bytes i wanna read at a time, where i read them)
  while (fread(&b, sizeof(b), 1, src)) {
    fwrite(&b, sizeof(b), 1, dst);
  }
  fclose(dst);
  fclose(src);
}
