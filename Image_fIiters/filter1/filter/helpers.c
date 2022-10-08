#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avr = 0;
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            avr= image[i][k].rgbtBlue + image[i][k].rgbtGreen + image[i][k].rgbtRed;
            avr = round(avr / 3.0);
            image[i][k].rgbtBlue = avr;
            image[i][k].rgbtGreen = avr;
            image[i][k].rgbtRed = avr;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagerow[width];
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            imagerow[k].rgbtBlue = image[i][k].rgbtBlue;
            imagerow[k].rgbtGreen = image[i][k].rgbtGreen;
            imagerow[k].rgbtRed = image[i][k].rgbtRed;
        }
        for(int j = 0, w = width - 1; j < width; j++)
        {
            image[i][j].rgbtBlue = imagerow[w].rgbtBlue;
            image[i][j].rgbtGreen = imagerow[w].rgbtGreen;
            image[i][j].rgbtRed = imagerow[w].rgbtRed;
            w--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagerow[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            imagerow[i][k].rgbtBlue = image[i][k].rgbtBlue;
            imagerow[i][k].rgbtGreen = image[i][k].rgbtGreen;
            imagerow[i][k].rgbtRed = image[i][k].rgbtRed;
        }
    }
    int row = 0;
    int col = 0;
    for(int j = 0; j < height; j++)
    {
        for(int m = 0; m < width; m++)
        {
            if(m - 1 >= 0)
            {
                col = m - 1;
            }
            else
            {
                col = m;
            }
            if(j - 1 >= 0)
            {
                row = j - 1;
            }
            else
            {
                row = j;
            }
            int avrBlue = 0;
            int avrGreen = 0;
            int avrRed = 0;
            double count = 0.0;
            for(int r = row; r <= j + 1; r++)
            {
                for(int c = col; c <= m + 1; c++)
                {
                    if(r >= height || c >= width)
                    {
                        break;
                    }
                    else
                    {
                        avrBlue += imagerow[r][c].rgbtBlue;
                        avrGreen += imagerow[r][c].rgbtGreen;
                        avrRed += imagerow[r][c].rgbtRed;
                        count++;
                    }
                }
            }
            image[j][m].rgbtBlue = round(avrBlue/count);
            image[j][m].rgbtGreen = round(avrGreen/count);
            image[j][m].rgbtRed = round(avrRed/count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagerow[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            imagerow[i][k].rgbtBlue = image[i][k].rgbtBlue;
            imagerow[i][k].rgbtGreen = image[i][k].rgbtGreen;
            imagerow[i][k].rgbtRed = image[i][k].rgbtRed;
        }
    }
    int row = 0;
    int col = 0;
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for(int j = 0; j < height; j++)
    {
        for(int m = 0; m < width; m++)
        {
            /*if(m - 1 >= 0)
            {
                col = m - 1;
            }
            else
            {
                col = m;
            }
            if(j - 1 >= 0)
            {
                row = j - 1;
            }
            else
            {
                row = j;
            }*/
            col = m - 1;
            row = j - 1;
            int avrBlue = 0;
            int avrGreen = 0;
            int avrRed = 0;
            int GxavrBlue = 0;
            int GxavrGreen = 0;
            int GxavrRed = 0;
            int GyavrBlue = 0;
            int GyavrGreen = 0;
            int GyavrRed = 0;
            int checkrow = 0;
            for(int r = row; r <= j + 1; r++)
            {
                int checkcol = 0;
                for(int c = col; c <= m + 1; c++)
                {
                    if(r >= height || c >= width)
                    {
                        GxavrBlue += 0 * Gx[checkrow][checkcol];
                        GxavrGreen += 0 * Gx[checkrow][checkcol];
                        GxavrRed += 0 * Gx[checkrow][checkcol];

                        //Gy Kernel
                        GyavrBlue += 0 * Gy[checkrow][checkcol];
                        GyavrGreen += 0 * Gy[checkrow][checkcol];
                        GyavrRed += 0 * Gy[checkrow][checkcol];
                    }
                    else if(c < 0 || r < 0)
                    {
                        GxavrBlue += 0 * Gx[checkrow][checkcol];
                        GxavrGreen += 0 * Gx[checkrow][checkcol];
                        GxavrRed += 0 * Gx[checkrow][checkcol];

                        //Gy Kernel
                        GyavrBlue += 0 * Gy[checkrow][checkcol];
                        GyavrGreen += 0 * Gy[checkrow][checkcol];
                        GyavrRed += 0 * Gy[checkrow][checkcol];
                    }
                    else
                    {
                        //Gx Kernel
                        GxavrBlue += imagerow[r][c].rgbtBlue * Gx[checkrow][checkcol];
                        GxavrGreen += imagerow[r][c].rgbtGreen * Gx[checkrow][checkcol];
                        GxavrRed += imagerow[r][c].rgbtRed * Gx[checkrow][checkcol];

                        //Gy Kernel
                        GyavrBlue += imagerow[r][c].rgbtBlue * Gy[checkrow][checkcol];
                        GyavrGreen += imagerow[r][c].rgbtGreen * Gy[checkrow][checkcol];
                        GyavrRed += imagerow[r][c].rgbtRed * Gy[checkrow][checkcol];
                    }
                    checkcol++;
                }
                checkrow++;
            }
            avrBlue = round( sqrt(pow(GxavrBlue, 2.0) + pow(GyavrBlue, 2.0)));
            avrGreen = round( sqrt(pow(GxavrGreen, 2.0) + pow(GyavrGreen, 2.0)));
            avrRed = round( sqrt(pow(GxavrRed, 2.0) + pow(GyavrRed, 2.0)));
            image[j][m].rgbtBlue = avrBlue < 255? avrBlue : 255;
            image[j][m].rgbtGreen = avrGreen < 255? avrGreen : 255;
            image[j][m].rgbtRed = avrRed < 255? avrRed : 255;
        }
    }
    return;
}
