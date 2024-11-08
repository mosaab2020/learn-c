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

int check_bounds(int height, int width, int i, int j) {
  /* TODO:
   * check if the pixel has neighbors on each side
   * each neighbor has his own return number
   */
  /* If the pixel on the left has an address that is more than or equal to 0(the
   start of the image);*/
  if (j - 1 >= 0) {
    return -1;
  } else if (j + 1 < width) {
    return 1;
  }

  if (i - 1 >= 0) {
    return -2;
  } else if (i + 1 < height) {
    return 2;
  }

  if (i - 1 >= 0 && j - 1 >= 0) {
    return -3;
  } else if (i + 1 < height && j + 1 < width) {
    return 3;
  }

  if (i + 1 < height && j - 1 >= 0) {
    return -4;
  } else if (i - 1 >= 0 && j + 1 < width) {
    return 4;
  }

  return 0;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  /*TODO: function buggy: -- FIXED
   * the bug is that when the image is copied it has not fully copied, so the
   * pixels that are not copied show as zeros.
   * NEED FIXED: change all img2 to image[i][j] -- DONE
   * function buggy:
   * need to count the pixels that are between pixels
   */

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
        if (check_bounds(height, width, i, j) == -1) {
          counter++;
          average_red += copy[i][j - 1].rgbtRed;
          average_green += copy[i][j - 1].rgbtGreen;
          average_blue += copy[i][j - 1].rgbtBlue;
        } else if (check_bounds(height, width, i, j) == 1) {
          counter++;
          average_red += copy[i][j + 1].rgbtRed;
          average_green += copy[i][j + 1].rgbtGreen;
          average_blue += copy[i][j + 1].rgbtBlue;
        } else if (check_bounds(height, width, i, j) == -2) {
          counter++;
          average_red += copy[i - 1][j].rgbtRed;
          average_green += copy[i - 1][j].rgbtGreen;
          average_blue += copy[i - 1][j].rgbtBlue;
        } else if (check_bounds(height, width, i, j) == 2) {
          counter++;
          average_red += copy[i + 1][j].rgbtRed;
          average_green += copy[i + 1][j].rgbtGreen;
          average_blue += copy[i + 1][j].rgbtBlue;
        } else if (check_bounds(height, width, i, j) == -3) {
          counter++;
          average_red += copy[i - 1][j - 1].rgbtRed;
          average_green += copy[i - 1][j - 1].rgbtGreen;
          average_blue += copy[i - 1][j - 1].rgbtBlue;
        } else if (check_bounds(height, width, i, j) == 3) {
          counter++;
          average_red += copy[i + 1][j + 1].rgbtRed;
          average_green += copy[i + 1][j + 1].rgbtGreen;
          average_blue += copy[i + 1][j + 1].rgbtBlue;
        } else if (check_bounds(height, width, i, j) == -4) {
          counter++;
          average_red += copy[i + 1][j - 1].rgbtRed;
          average_green += copy[i + 1][j - 1].rgbtGreen;
          average_blue += copy[i + 1][j - 1].rgbtBlue;
        } else if (check_bounds(height, width, i, j) == 4) {
          counter++;
          average_red += copy[i - 1][j + 1].rgbtRed;
          average_green += copy[i - 1][j + 1].rgbtGreen;
          average_blue += copy[i - 1][j + 1].rgbtBlue;
        }
      }

      image[i][j].rgbtBlue = round(average_blue / counter);
      image[i][j].rgbtGreen = round(average_green / counter);
      image[i][j].rgbtRed = round(average_red / counter);
    }
  }
  return;
}
