#include "helpers.h"
#include <math.h>
#include <stdio.h>

RGBTRIPLE pixel(int r, int g, int b) {
  RGBTRIPLE p;
  p.rgbtRed = r;
  p.rgbtGreen = g;
  p.rgbtBlue = b;
  return p;
}

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

int average_G(int height, int width, RGBTRIPLE image[height][width], int i,
              int j) {
  int average_Gx_red =
      image[i + 1][j - 1].rgbtRed * -1 + image[i][j - 1].rgbtRed * -2 +
      image[i - 1][j - 1].rgbtRed * -1 + image[i + 1][j + 1].rgbtRed * 1 +
      image[i - 1][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 2;
  int average_Gx_green =
      image[i + 1][j - 1].rgbtGreen * -1 + image[i][j - 1].rgbtGreen * -2 +
      image[i - 1][j - 1].rgbtGreen * -1 + image[i + 1][j + 1].rgbtGreen * 1 +
      image[i - 1][j + 1].rgbtGreen * 1 + image[i][j + 1].rgbtGreen * 2;
  int average_Gx_blue =
      image[i + 1][j - 1].rgbtBlue * -1 + image[i][j - 1].rgbtBlue * -2 +
      image[i - 1][j - 1].rgbtBlue * -1 + image[i + 1][j + 1].rgbtBlue * 1 +
      image[i - 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue * 2;

  int average_Gy_red =
      image[i - 1][j - 1].rgbtRed * -1 + image[i + 1][j - 1].rgbtRed * 1 +
      image[i - 1][j].rgbtRed * -2 + image[i + 1][j].rgbtRed * 2 +
      image[i - 1][j + 1].rgbtRed * -1 + image[i + 1][j + 1].rgbtRed * 1;
  int average_Gy_green =
      image[i - 1][j - 1].rgbtGreen * -1 + image[i + 1][j - 1].rgbtGreen * 1 +
      image[i - 1][j].rgbtGreen * -2 + image[i + 1][j].rgbtGreen * 2 +
      image[i - 1][j + 1].rgbtGreen * -1 + image[i + 1][j + 1].rgbtGreen * 1;
  int average_Gy_blue =
      image[i - 1][j - 1].rgbtBlue * -1 + image[i + 1][j - 1].rgbtBlue * 1 +
      image[i - 1][j].rgbtBlue * -2 + image[i + 1][j].rgbtBlue * 2 +
      image[i - 1][j + 1].rgbtBlue * -1 + image[i + 1][j + 1].rgbtBlue * 1;

  printf("%i\n", average_Gx_red);
  printf("%i\n", average_Gx_green);
  printf("%i\n", average_Gx_blue);
  printf("%i\n", average_Gy_red);
  printf("%i\n", average_Gy_green);
  printf("%i\n", average_Gy_blue);
  return 0;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  // Placeholder
  height = 3;
  width = 3;
  // Image with varying colors
  RGBTRIPLE img2[3][3];
  img2[0][0] = pixel(0, 0, 255);
  img2[0][1] = pixel(128, 0, 128);
  img2[0][2] = pixel(255, 0, 0);

  img2[1][0] = pixel(0, 0, 255);
  img2[1][1] = pixel(128, 0, 128);
  img2[1][2] = pixel(255, 0, 0);

  img2[2][0] = pixel(0, 0, 255);
  img2[2][1] = pixel(128, 0, 128);
  img2[2][2] = pixel(255, 0, 0);

  /*RGBTRIPLE img5[4][4];*/
  /*img5[0][0] = pixel(10, 10, 10);*/
  /*img5[0][1] = pixel(10, 10, 10);*/
  /*img5[0][2] = pixel(10, 10, 10);*/
  /*img5[0][3] = pixel(10, 10, 10);*/
  /*img5[1][0] = pixel(10, 10, 10);*/
  /*img5[1][1] = pixel(10, 10, 10);*/
  /*img5[1][2] = pixel(10, 10, 10);*/
  /*img5[1][3] = pixel(10, 10, 10);*/
  /*img5[2][0] = pixel(10, 10, 10);*/
  /*img5[2][1] = pixel(10, 10, 10);*/
  /*img5[2][2] = pixel(10, 10, 10);*/
  /*img5[2][3] = pixel(10, 10, 10);*/
  /*img5[3][0] = pixel(10, 10, 10);*/
  /*img5[3][1] = pixel(10, 10, 10);*/
  /*img5[3][2] = pixel(10, 10, 10);*/
  /*img5[3][3] = pixel(10, 10, 10);*/
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      image[i][j] = img2[i][j];
    }
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // if the pixel has 8 neighbors
      int Gx;
      int Gy;
      if (j - 1 >= 0 && j + 1 < width && i - 1 >= 0 && i + 1 < height) {
        average_G(height, width, img2, i, j);
      }
    }
  }
  return;
}
