#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  /* TODO:
   * calulate the average pixel value -- done
   * set each color value to the average value -- done
   */
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE pixel = image[i][j];
      int average =
          round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
      image[i][j].rgbtRed = average;
      image[i][j].rgbtGreen = average;
      image[i][j].rgbtBlue = average;
    }
  }
  return;
}

int sepia_helper(int num) {
  if (num > 255) {
    num = 255;
  }
  return num;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      RGBTRIPLE pixel = image[i][j];
      int sepiaRed =
          sepia_helper(round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen +
                             0.189 * pixel.rgbtBlue));
      int sepiaGreen =
          sepia_helper(round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen +
                             0.168 * pixel.rgbtBlue));
      int sepiaBlue =
          sepia_helper(round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen +
                             0.131 * pixel.rgbtBlue));

      image[i][j].rgbtRed = sepiaRed;
      image[i][j].rgbtGreen = sepiaGreen;
      image[i][j].rgbtBlue = sepiaBlue;

      // not working code -- buggy
      /*if (sizeof(image[i][j].rgbtRed) > sizeof(BYTE)) {*/
      /*  image[i][j].rgbtRed = 255;*/
      /*}*/
      /*if (sizeof(image[i][j].rgbtGreen) > sizeof(BYTE)) {*/
      /*  image[i][j].rgbtGreen = 255;*/
      /*}*/
      /*if (sizeof(image[i][j].rgbtBlue) > sizeof(BYTE)) {*/
      /*  image[i][j].rgbtBlue = 255;*/
      /*}*/
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  // placeholder
  RGBTRIPLE buffer;
  for (int i = 0; i < height; i++) {
    for (int j = 0, last = width; j < width / 2; j++) {
      buffer = image[i][j];
      image[i][j] = image[i][last - j - 1];
      image[i][last - j - 1] = buffer;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  // placeholder
  return;
}
