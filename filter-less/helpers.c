#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int b = image[i][j].rgbtBlue;
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            float average = (b + r + g)/3.0;
            average = roundf (average);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float b = image[i][j].rgbtBlue;
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            int newr;
            int newg;
            int newb;

            newr = .393 * r + .769 * g + .189 * b;
            newg = .349 * r + .686 * g + .168 * b;
            newb = .272 * r + .534 * g + .131 * b;

            newr = (int) newr;
            newg = (int) newg;
            newb = (int) newb;

            if (newr > 255)
            {
                newr = 255;
            }
            if (newg > 255)
            {
                newg = 255;
            }
            if (newb > 255)
            {
                newb = 255;
            }

            image[i][j].rgbtBlue = newb;
            image[i][j].rgbtRed = newr;
            image[i][j].rgbtGreen = newg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            int b = image[i][j].rgbtBlue;
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;

            int b1 = image[i][width - j].rgbtBlue;
            int r1 = image[i][width - j].rgbtRed;
            int g1 = image[i][width - j].rgbtGreen;

            image[i][j].rgbtBlue = b1;
            image[i][j].rgbtRed = r1;
            image[i][j].rgbtGreen = g1;

            image[i][width - j ].rgbtBlue = b;
            image[i][width - j ].rgbtRed = r;
            image[i][width - j ].rgbtGreen = g;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE duplicate [height][width];
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            duplicate[i][j].rgbtBlue = image[i][j].rgbtBlue;
            duplicate[i][j].rgbtRed = image[i][j].rgbtRed;
            duplicate[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    int min = -1;
    int max = 1;
    for (int i = 0; i < height; i++) //i = altura original do pixel = y
    {
        for(int j = 0; j < width; j++) //j = largura original = x
        {
            int d = 0;
            int Rfinal = 0;
            int Gfinal = 0;
            int Bfinal = 0;
            for (int x = min; x <= max; x++)
            {
                for(int y = min; y<=max; y++)
                    {
                        int xv = 0;
                        int yv = 0;
                        xv = x + i;
                        yv = y + j;

                        if ((0 <= xv && xv < height) && (0 <= yv && yv < width))
                        {
                            Bfinal = Bfinal + duplicate[xv][yv].rgbtBlue;
                            Rfinal = Rfinal + duplicate[xv][yv].rgbtRed;
                            Gfinal = Gfinal + duplicate[xv][yv].rgbtGreen;
                            d++;
                        }
                    }
            }
        Rfinal = Rfinal/d;
        Gfinal = Gfinal/d;
        Bfinal = Bfinal/d;
        image[i][j].rgbtBlue = (int)Bfinal;
        image[i][j].rgbtRed =  (int)Rfinal;
        image[i][j].rgbtGreen = (int)Gfinal;
        }
    }
    return;
}