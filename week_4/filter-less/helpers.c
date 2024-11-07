#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating the average of RGB values and rounding
            int average = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Setting all RGB values to the calculated average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Storing original RGB values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Calculating sepia tone for each color channel and rounding
            int sepiaRed =
                (int) round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen =
                (int) round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue =
                (int) round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Capping each value at 255 if it exceeds the maximum
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swapping pixels from left to right
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating a temporary copy of the image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Applying blur to each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Iterating over a 3x3 grid around the pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Ensuring neighbor pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalRed += temp[ni][nj].rgbtRed;
                        totalGreen += temp[ni][nj].rgbtGreen;
                        totalBlue += temp[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Setting the blurred color to the average of the neighboring pixels and rounding
            image[i][j].rgbtRed = (int) round(totalRed / (float) count);
            image[i][j].rgbtGreen = (int) round(totalGreen / (float) count);
            image[i][j].rgbtBlue = (int) round(totalBlue / (float) count);
        }
    }
}
