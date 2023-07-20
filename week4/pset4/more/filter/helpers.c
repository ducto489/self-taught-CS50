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
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round((long double)(image[i][j].rgbtBlue +
                                  image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate brand new value
            (.393 * (long double)image[i][j].rgbtRed + .769 * (long double)image[i][j].rgbtGreen +
             .189 * (long double)image[i][j].rgbtBlue);
            nd(.349 * (long double)image[i][j].rgbtRed + .686 * (long double)image[i][j].rgbtGreen +
               .168 * (long double)image[i][j].rgbtBlue);
            d(.272 * (long double)image[i][j].rgbtRed + .534 * (long double)image[i][j].rgbtGreen +
              .131 * (long double)image[i][j].rgbtBlue);

            //Check if the new value is larger then 255
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE glass;
    int half = round((double)width / 2);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half; j++)
        {
            //Swap??
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
    //Create a new array to save new value
    RGBTRIPLE array[height][width];

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
            array[i][j].rgbtBlue = round((float)sumBlue / total);
            array[i][j].rgbtRed = round((float)sumRed / total);
            array[i][j].rgbtGreen = round((float)sumGreen / total);
        }
    }

    //Save new value to original array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = array[i][j];
        }
    }

    return;
}
