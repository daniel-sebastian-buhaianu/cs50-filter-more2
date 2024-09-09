#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double gray =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < k; j++, k--)
        {
            // swap image[i][j] with image[i][k]
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    const int MAX_NEIGHBOURS = 8;
    const int DX[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int DY[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int neighboursCount = 1;
            double averageRed = copy[i][j].rgbtRed;
            double averageGreen = copy[i][j].rgbtGreen;
            double averageBlue = copy[i][j].rgbtBlue;

            for (int k = 0; k < MAX_NEIGHBOURS; k++)
            {
                int row = i + DX[k];
                int col = j + DY[k];

                // Check if image[row][col] is neighbour of image[i][j]
                if (row >= 0 && row < height && col >= 0 && col < width)
                {
                    neighboursCount++;

                    averageRed += copy[row][col].rgbtRed;
                    averageGreen += copy[row][col].rgbtGreen;
                    averageBlue += copy[row][col].rgbtBlue;
                }
            }

            averageRed = round(averageRed / neighboursCount);
            averageGreen = round(averageGreen / neighboursCount);
            averageBlue = round(averageBlue / neighboursCount);

            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
