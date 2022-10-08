#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int Sblue = 0;
    int Sgreen = 0;
    int Sred = 0;
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            Sblue= round(0.131 * image[i][k].rgbtBlue + 0.534 * image[i][k].rgbtGreen + 0.272 * image[i][k].rgbtRed);
            Sgreen= round(0.168 * image[i][k].rgbtBlue + 0.686 * image[i][k].rgbtGreen + 0.349 * image[i][k].rgbtRed);
            Sred= round(0.189 * image[i][k].rgbtBlue + 0.769 * image[i][k].rgbtGreen + 0.393 * image[i][k].rgbtRed);
            image[i][k].rgbtBlue = Sblue < 255? Sblue : 255 ;
            image[i][k].rgbtGreen = Sgreen < 255? Sgreen : 255;
            image[i][k].rgbtRed = Sred < 255? Sred: 255;
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
