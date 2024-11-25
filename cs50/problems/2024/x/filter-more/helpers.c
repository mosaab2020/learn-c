#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
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
  // Create a copy of image
  RGBTRIPLE copy[height][width];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      copy[i][j] = image[i][j];
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // Check if the pixel has neighbors on all sides
      int average_red = 0;
      int average_green = 0;
      int average_blue = 0;
      float counter = 1;
      if (j - 1 >= 0 && j + 1 < width && i - 1 >= 0 && i + 1 < height) {
        average_red = copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed +
                      copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed +
                      copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                      copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                      copy[i - 1][j + 1].rgbtRed;
        average_green =
            copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen +
            copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
            copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
            copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
            copy[i - 1][j + 1].rgbtGreen;
        average_blue = copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue +
                       copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                       copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                       copy[i - 1][j - 1].rgbtBlue +
                       copy[i + 1][j - 1].rgbtBlue +
                       copy[i - 1][j + 1].rgbtBlue;
        counter = 9.0;
      } else {
        average_red += copy[i][j].rgbtRed;
        average_green += copy[i][j].rgbtGreen;
        average_blue += copy[i][j].rgbtBlue;
        if (j - 1 >= 0) {
          counter++;
          average_red += copy[i][j - 1].rgbtRed;
          average_green += copy[i][j - 1].rgbtGreen;
          average_blue += copy[i][j - 1].rgbtBlue;
        }
        if (j + 1 < width) {
          counter++;
          average_red += copy[i][j + 1].rgbtRed;
          average_green += copy[i][j + 1].rgbtGreen;
          average_blue += copy[i][j + 1].rgbtBlue;
        }
        if (i - 1 >= 0) {
          counter++;
          average_red += copy[i - 1][j].rgbtRed;
          average_green += copy[i - 1][j].rgbtGreen;
          average_blue += copy[i - 1][j].rgbtBlue;
        }
        if (i + 1 < height) {
          counter++;
          average_red += copy[i + 1][j].rgbtRed;
          average_green += copy[i + 1][j].rgbtGreen;
          average_blue += copy[i + 1][j].rgbtBlue;
        }
        if (i - 1 >= 0 && j - 1 >= 0) {
          counter++;
          average_red += copy[i - 1][j - 1].rgbtRed;
          average_green += copy[i - 1][j - 1].rgbtGreen;
          average_blue += copy[i - 1][j - 1].rgbtBlue;
        }
        if (i + 1 < height && j + 1 < width) {
          counter++;
          average_red += copy[i + 1][j + 1].rgbtRed;
          average_green += copy[i + 1][j + 1].rgbtGreen;
          average_blue += copy[i + 1][j + 1].rgbtBlue;
        }
        if (i + 1 < height && j - 1 >= 0) {
          counter++;
          average_red += copy[i + 1][j - 1].rgbtRed;
          average_green += copy[i + 1][j - 1].rgbtGreen;
          average_blue += copy[i + 1][j - 1].rgbtBlue;
        }
        if (i - 1 >= 0 && j + 1 < width) {
          counter++;
          average_red += copy[i - 1][j + 1].rgbtRed;
          average_green += copy[i - 1][j + 1].rgbtGreen;
          average_blue += copy[i - 1][j + 1].rgbtBlue;
        }
      }

      image[i][j].rgbtBlue = round(average_blue / counter);
      image[i][j].rgbtGreen = round(average_green / counter);
      image[i][j].rgbtRed = round(average_red / counter);
      /*printf("%i, %i, %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen,*/
      /*       image[i][j].rgbtBlue);*/
    }
  }
  return;
}

bool check_pixel(int height, int width, int i, int j) {
  // some help from the duck
  return (i >= 0 && i < height && j >= 0 && j < width);
}

int check_overflow(int num) {
  if (num > 255) {
    num = 255;
  }
  return num;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  /* NOTES:
   * j-1, i-1 | j, i-1 | j+1, i-1
   * j-1, i   | j, i   | j+1, i
   * j-1, i+1 | j, i+1 | j+1, i+1
   */
  int kernelGx[3][3] = {
      {-1, 0, 1},
      {-2, 0, 2},
      {-1, 0, 1},
  };
  int kernelGy[3][3] = {
      {-1, -2, -1},
      {0, 0, 0},
      {1, 2, 1},
  };

  RGBTRIPLE copy[height][width];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      copy[i][j] = image[i][j];
    }
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // if the pixel has 8 neighbors
      int Gx_red = 0;
      int Gx_green = 0;
      int Gx_blue = 0;

      int Gy_red = 0;
      int Gy_green = 0;
      int Gy_blue = 0;
      for (int y = -1; y < 2; y++) {
        for (int x = -1; x < 2; x++) {
          if (check_pixel(height, width, i + y, j + x) == true) {
            Gx_red += copy[i + y][j + x].rgbtRed * kernelGx[y + 1][x + 1];
            Gy_red += copy[i + y][j + x].rgbtRed * kernelGy[y + 1][x + 1];

            Gx_green += copy[i + y][j + x].rgbtGreen * kernelGx[y + 1][x + 1];
            Gy_green += copy[i + y][j + x].rgbtGreen * kernelGy[y + 1][x + 1];

            Gx_blue += copy[i + y][j + x].rgbtBlue * kernelGx[y + 1][x + 1];
            Gy_blue += copy[i + y][j + x].rgbtBlue * kernelGy[y + 1][x + 1];
          }
        }
      }
      image[i][j].rgbtRed =
          check_overflow(round(sqrt(pow(Gx_red, 2) + pow(Gy_red, 2))));
      image[i][j].rgbtGreen =
          check_overflow(round(sqrt(pow(Gx_green, 2) + pow(Gy_green, 2))));
      image[i][j].rgbtBlue =
          check_overflow(round(sqrt(pow(Gx_blue, 2) + pow(Gy_blue, 2))));
    }
  }
  return;
}
