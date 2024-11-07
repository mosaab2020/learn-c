#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

RGBTRIPLE new_pixel(int r, int g, int b) {
  RGBTRIPLE p;
  p.rgbtRed = r;
  p.rgbtGreen = g;
  p.rgbtBlue = b;
  return p;
}

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

/*bool check_bound(int height, int width, int i, int j) {*/
/*  if (j - 1 >= 0 && j + 1 < width && i - 1 >= 0 && i + 1 < height) {*/
/*    return true;*/
/*  }*/
/*  return false;*/
/*}*/

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  /*TODO: function buggy:
   * the bug is that when the image is copied it has not fully copied, so the
   * pixels that are not copied show as zeros.
   * NEED FIXED change all img2 to image[i][j]
   */

  RGBTRIPLE img2[3][3];
  img2[0][0] = new_pixel(10, 20, 30);
  img2[0][1] = new_pixel(40, 50, 60);
  img2[0][2] = new_pixel(70, 80, 90);
  img2[1][0] = new_pixel(110, 130, 140);
  img2[1][1] = new_pixel(120, 140, 150);
  img2[1][2] = new_pixel(130, 150, 160);
  img2[2][0] = new_pixel(200, 210, 220);
  img2[2][1] = new_pixel(220, 230, 240);
  img2[2][2] = new_pixel(240, 250, 255);

  // Create a copy of image
  RGBTRIPLE copy[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      copy[i][j] = img2[i][j];
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j - 1 >= 0 && j + 1 < width && i - 1 >= 0 && i + 1 < height) {
        int average_red = sepia_helper(
            round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed +
                   copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed +
                   copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                   copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                   copy[i - 1][j + 1].rgbtRed) /
                  9.00));
        int average_green = sepia_helper(
            round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen +
                   copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                   copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                   copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                   copy[i - 1][j + 1].rgbtGreen) /
                  9.00));
        int average_blue = sepia_helper(
            round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue +
                   copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                   copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                   copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                   copy[i - 1][j + 1].rgbtBlue) /
                  9.00));
        img2[i][j].rgbtBlue = average_blue;
        img2[i][j].rgbtGreen = average_green;
        img2[i][j].rgbtRed = average_red;
        /*printf("(%i, %i, %i)\n", img2[i][j].rgbtRed, img2[i][j].rgbtGreen,*/
        /*       img2[i][j].rgbtBlue);*/
      }
    }
  }
  return;
}
