#include "helpers.h"
#include <math.h>

// sepia constants for Red
#define SEPIA_RED_1 0.393
#define SEPIA_RED_2 0.769
#define SEPIA_RED_3 0.189

// sepia constants for Green
#define SEPIA_GREEN_1 0.349
#define SEPIA_GREEN_2 0.686
#define SEPIA_GREEN_3 0.168

// sepia constants for Blue
#define SEPIA_BLUE_1 0.272
#define SEPIA_BLUE_2 0.534
#define SEPIA_BLUE_3 0.131
//dont ask why they work & who made them althought I am curious about it myself
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // store sum
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen;
            // using round \ here but can use ceil as well
            int avg = (int) round(sum / 3.0);
            // update values and why not all in one line? well, deal with it!
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
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

            int sepiaRed =
                round(SEPIA_RED_1 * image[i][j].rgbtRed + SEPIA_RED_2 * image[i][j].rgbtGreen +
                      SEPIA_RED_3 * image[i][j].rgbtBlue);
            int sepiaGreen =
                round(SEPIA_GREEN_1 * image[i][j].rgbtRed + SEPIA_GREEN_2 * image[i][j].rgbtGreen +
                      SEPIA_GREEN_3 * image[i][j].rgbtBlue);
            int sepiaBlue =
                round(SEPIA_BLUE_1 * image[i][j].rgbtRed + SEPIA_BLUE_2 * image[i][j].rgbtGreen +
                      SEPIA_BLUE_3 * image[i][j].rgbtBlue);

            /* WARNING!!! ternary operators ahead KEEP YOUR EYES OPEN */

            // to make sure no value is greater than 255
            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
          //if you don't understand them don't worry its just IF_ELSE less steps
          // not ideal for 'production' level code

            // updagting the values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally

// helper function
void swaprgb(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            // width-j-1 is a formula to get the opposite pixel
            swaprgb(&image[i][j], &image[i][width - j - 1]);
          /*why width-j-1 and not a variable which stores just
          the difference from middle to current pixel (i.e diffp = middle - j); 
          I suggest you try it and see where you end up at :) */
        }
    }
    return;
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

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;
            // di & dj are the offsets
            // ni & nj are the actual indices made from adding di & dj
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Checking if the neighboring pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // take values from the neighboring pixel
                        // add its RGB values to the sum
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average RGB values & assign them to the new image
            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }
    return;
}

//sayonara :)
