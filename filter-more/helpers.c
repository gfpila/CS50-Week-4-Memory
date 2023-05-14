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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Duplicate array
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

    //Matrizes definitions
    int Gx[3][3] = {{-1, 0, 1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,2}};
    int min = -1;
    int max = 1;


    for (int i = 0; i < height; i++) //primeira coluna
    {
        for(int j = 0; j < width; j++) //primeiro pixel
        {
            int YRfinal = 0;
            int YGfinal = 0;
            int YBfinal = 0;
            int XRfinal = 0;
            int XGfinal = 0;
            int XBfinal = 0;
            int Bfinal = 0;
            int Rfinal = 0;
            int Gfinal = 0;

            for (int x = min, n = 0; x <= max; x++, n++)
            {
                for(int y = min, k = 0; y<=max; y++, k++)
                {
                    int xv = 0;
                    int yv = 0;
                    xv = x + i;
                    yv = y + j;
                    if ((0 <= xv && xv < height) && (0 <= yv && yv < width))
                    {
                        XBfinal = XBfinal + (duplicate[xv][yv].rgbtBlue * Gx[n][k]);
                        XRfinal = XRfinal + (duplicate[xv][yv].rgbtRed *  Gx[n][k]);
                        XGfinal = XGfinal + (duplicate[xv][yv].rgbtGreen * Gx[n][k]);

                        YBfinal = YBfinal + (duplicate[xv][yv].rgbtBlue * Gy[n][k]);
                        YRfinal = YRfinal + (duplicate[xv][yv].rgbtRed *  Gy[n][k]);
                        YGfinal = YGfinal + (duplicate[xv][yv].rgbtGreen * Gy[n][k]);
                    }
                }
            }

        Gfinal = (int) sqrt(XGfinal * XGfinal +  YGfinal * YGfinal);
        Rfinal = (int) sqrt(XRfinal * XRfinal + YRfinal * YRfinal);
        Bfinal = (int) sqrt(XBfinal * XBfinal + YBfinal * YBfinal);

        if(Gfinal > 255)
        {
            Gfinal = 255;
        }
        if(Rfinal > 255)
        {
            Rfinal = 255;
        }
        if(Bfinal > 255)
        {
            Bfinal = 255;
        }

        image[i][j].rgbtBlue = (int) Bfinal;
        image[i][j].rgbtRed =  (int) Rfinal;
        image[i][j].rgbtGreen = (int) Gfinal;
        }
    }

    return;
}
