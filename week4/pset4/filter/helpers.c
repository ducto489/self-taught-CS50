#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE glass;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2 + 1; j++)
        {
            glass.rgbtBlue = image[i][j].rgbtBlue;
            glass.rgbtRed = image[i][j].rgbtRed;
            glass.rgbtGreen = image[i][j].rgbtGreen;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;

            image[i][width - j - 1].rgbtBlue = glass.rgbtBlue;
            image[i][width - j - 1].rgbtRed = glass.rgbtRed;
            image[i][width - j - 1].rgbtGreen = glass.rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = image[i][j].rgbtRed, sumGreen = image[i][j].rgbtGreen, sumBlue = image[i][j].rgbtBlue, total = 1;

            //Check if top-left corner is valid
            if (i > 0 && j > 0)
            {
                sumRed = sumRed + image[i - 1][j - 1].rgbtRed;
                sumBlue = sumBlue + image[i - 1][j - 1].rgbtBlue;
                sumGreen = sumGreen + image[i - 1][j - 1].rgbtGreen;
                total++;
            }
            //Check if top-middle is valid
            if (i > 0)
            {
                sumRed = sumRed + image[i - 1][j].rgbtRed;
                sumBlue = sumBlue + image[i - 1][j].rgbtBlue;
                sumGreen = sumGreen + image[i - 1][j].rgbtGreen;
                total++;
            }
            //Check if top-right corner is valid
            if (i > 0 && j + 1 < width)
            {
                sumRed = sumRed + image[i - 1][j + 1].rgbtRed;
                sumBlue = sumBlue + image[i - 1][j + 1].rgbtBlue;
                sumGreen = sumGreen + image[i - 1][j + 1].rgbtGreen;
                total++;
            }
            //Check if middle-left is valid
            if (j > 0)
            {
                sumRed = sumRed + image[i][j - 1].rgbtRed;
                sumBlue = sumBlue + image[i][j - 1].rgbtBlue;
                sumGreen = sumGreen + image[i][j - 1].rgbtGreen;
                total++;
            }
            //Check if middle-right is valid
            if (j + 1 < width)
            {
                sumRed = sumRed + image[i][j + 1].rgbtRed;
                sumBlue = sumBlue + image[i][j + 1].rgbtBlue;
                sumGreen = sumGreen + image[i][j + 1].rgbtGreen;
                total++;
            }
            //Check if bottom-left corner is valid
            if (i + 1 < height && j > 0)
            {
                sumRed = sumRed + image[i + 1][j - 1].rgbtRed;
                sumBlue = sumBlue + image[i + 1][j - 1].rgbtBlue;
                sumGreen = sumGreen + image[i + 1][j - 1].rgbtGreen;
                total++;
            }
            //Check if bottom-middle is valid
            if (i + 1 < height)
            {

                sumRed = sumRed + image[i + 1][j].rgbtRed;
                sumBlue = sumBlue + image[i + 1][j].rgbtBlue;
                sumGreen = sumGreen + image[i + 1][j].rgbtGreen;
                total++;
            }
            //Check if bottom-right corner is valid
            if (i + 1 < height && j + 1 < width)
            {
                sumRed = sumRed + image[i + 1][j + 1].rgbtRed;
                sumBlue = sumBlue + image[i + 1][j + 1].rgbtBlue;
                sumGreen = sumGreen + image[i + 1][j + 1].rgbtGreen;
                total++;
            }
            image[i][j].rgbtBlue = round((float)sumBlue / total);
            image[i][j].rgbtRed = round((float)sumRed / total);
            image[i][j].rgbtGreen = round((float)sumGreen / total);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE array[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed = 0, GxGreen = 0, GxBlue = 0, GyRed = 0, GyGreen = 0, GyBlue = 0;

            //Find Gx and Gy for each coulor
            //Check if top-left corner is valid
            if (i > 0 && j > 0)
            {
                GxRed = GxRed - image[i - 1][j - 1].rgbtRed;
                GxBlue = GxBlue - image[i - 1][j - 1].rgbtBlue;
                GxGreen = GxGreen - image[i - 1][j - 1].rgbtGreen;

                GyRed = GyRed - image[i - 1][j - 1].rgbtRed;
                GyBlue = GyBlue - image[i - 1][j - 1].rgbtBlue;
                GyGreen = GyGreen - image[i - 1][j - 1].rgbtGreen;
            }
            //Check if top-middle is valid
            if (i > 0)
            {
                GyRed = GyRed - 2 * image[i - 1][j].rgbtRed;
                GyBlue = GyBlue - 2 * image[i - 1][j].rgbtBlue;
                GyGreen = GyGreen - 2 * image[i - 1][j].rgbtGreen;
            }
            //Check if top-right corner is valid
            if (i > 0 && j + 1 < width)
            {
                GxRed = GxRed + image[i - 1][j + 1].rgbtRed;
                GxBlue = GxBlue + image[i - 1][j + 1].rgbtBlue;
                GxGreen = GxGreen + image[i - 1][j + 1].rgbtGreen;

                GyRed = GyRed - image[i - 1][j + 1].rgbtRed;
                GyBlue = GyBlue - image[i - 1][j + 1].rgbtBlue;
                GyGreen = GyGreen - image[i - 1][j + 1].rgbtGreen;
            }
            //Check if middle-left is valid
            if (j > 0)
            {
                GxRed = GxRed - 2 * image[i][j - 1].rgbtRed;
                GxBlue = GxBlue - 2 * image[i][j - 1].rgbtBlue;
                GxGreen = GxGreen - 2 * image[i][j - 1].rgbtGreen;
            }
            //Check if middle-right is valid
            if (j + 1 < width)
            {
                GxRed = GxRed + 2 * image[i][j + 1].rgbtRed;
                GxBlue = GxBlue + 2 * image[i][j + 1].rgbtBlue;
                GxGreen = GxGreen + 2 * image[i][j + 1].rgbtGreen;
            }
            //Check if bottom-left corner is valid
            if (i + 1 < height && j > 0)
            {
                GxRed = GxRed - image[i + 1][j - 1].rgbtRed;
                GxBlue = GxBlue - image[i + 1][j - 1].rgbtBlue;
                GxGreen = GxGreen - image[i + 1][j - 1].rgbtGreen;

                GyRed = GyRed + image[i + 1][j - 1].rgbtRed;
                GyBlue = GyBlue + image[i + 1][j - 1].rgbtBlue;
                GyGreen = GyGreen + image[i + 1][j - 1].rgbtGreen;
            }
            //Check if bottom-middle is valid
            if (i + 1 < height)
            {

                GyRed = GyRed + 2 * image[i + 1][j].rgbtRed;
                GyBlue = GyBlue + 2 * image[i + 1][j].rgbtBlue;
                GyGreen = GyGreen + 2 * image[i + 1][j].rgbtGreen;
            }
            //Check if bottom-right corner is valid
            if (i + 1 < height && j + 1 < width)
            {
                GxRed = GxRed + image[i + 1][j + 1].rgbtRed;
                GxBlue = GxBlue + image[i + 1][j + 1].rgbtBlue;
                GxGreen = GxGreen + image[i + 1][j + 1].rgbtGreen;

                GyRed = GyRed + image[i + 1][j + 1].rgbtRed;
                GyBlue = GyBlue + image[i + 1][j + 1].rgbtBlue;
                GyGreen = GyGreen + image[i + 1][j + 1].rgbtGreen;
            }
            array[i][j].rgbtBlue = round(sqrt((double)GxBlue * GxBlue + GyBlue * GyBlue));
            array[i][j].rgbtRed = round(sqrt((double)GxRed * GxRed + GyRed * GyRed));
            array[i][j].rgbtGreen = round(sqrt((double)GxGreen * GxGreen + GyGreen * GyGreen));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = array[i][j];
        }
    }
    return;
}
