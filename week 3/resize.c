// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "bmp.h"

bool IsZeroMultipier(char *multiplier);
bool checkIfBMPFile(char *file);

int main(int argc, char *argv[])
{
    int length = argc;
    int multiplierLength = strlen(argv[1]);

    // Greater than 3 digit number, exit right away.
    if (multiplierLength > 3)
    {
        printf("Must use a positive integer less than or equal to 100\n");
        return 1;
    }

    // Loop through each digit make sure it is a valid number.
    for (int i = 0; i < multiplierLength; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Must use a positive integer less than or equal to 100\n");
            return 1;
        }
    }

    // Convert string to integer
    int converted = atoi(argv[1]);

    if (argc != 4)
    {
        printf("Terminal command must like look this: ./resize 2 small.bmp larger.bmp\n");
        return 1;
    }

    if (((converted < 0) || (converted > 100)))
    {
        printf("Must use a positive integer less than or equal to 100\n");
        return 1;
    }

    if (!checkIfBMPFile(argv[2]) || !checkIfBMPFile(argv[3]))
    {
        printf("Must use a .bmp file format!\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    //hold values of original width and height
    int originalWidth = bi.biWidth;
    int originalHeight = abs(bi.biHeight);

    // Create new width, height, Size Image and File Size
    bi.biWidth = bi.biWidth *= converted;
    bi.biHeight = bi.biHeight *= converted;
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Array to hold pixels of original image
    RGBTRIPLE pixelArray[originalWidth * originalHeight];
    // Pointer to hold new scanline
    RGBTRIPLE *scanline = malloc((originalWidth * converted) * sizeof(RGBTRIPLE));

    // Counter for each pixel in original bmp file.
    int pixelCounter = 0;
    // Count number of pixels in scanLine
    int scanlinePixels = 0;
    // Iteratator for pixelArray
    int pixelIterator = 0;

    // determine original padding
    int originalPadding = (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Get all pixels of original image.
    for (int i = 0, biHeight = abs(originalHeight); i < biHeight; i++)
    {
        // iterate over pixels in original scanline
        for (int j = 0; j < (originalWidth + originalPadding); j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (triple.rgbtBlue != 0 || triple.rgbtGreen != 0 || triple.rgbtRed != 0)
            {
                // Put the pixel in the array.
                pixelArray[pixelCounter] = triple;
                // Increment pixelCounter for each pixel found
                pixelCounter ++;
            }
        }
    }

    // iterate over new .bmp dimensions
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in new scanline width
        for (int j = 0; j < bi.biWidth; j++)
        {
            // RGBTRIPLE *pixel = malloc((1) * sizeof(RGBTRIPLE));
            //pixel = &triple;

            // if scanlinePixels is at (originalWidth * converted)
            if (scanlinePixels == (originalWidth * converted))
            {
                // Continue to next iteration
                continue;
            }

            // Loop n times, based on converted
            for (int k = 0; k < converted; k++)
            {
                // Write pixelArray[pixelIterator] to outfile
                fwrite(&pixelArray[pixelIterator], sizeof(RGBTRIPLE), 1, outptr);
                // Fill in a a byte for scanline
                scanline[scanlinePixels] = pixelArray[pixelIterator];
                // Increment scanlinePixels
                scanlinePixels ++;
            }

            // increment pixelIterator
            pixelIterator ++;
        }

        // skip over padding, if any
        fseek(inptr, newPadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int l = 0; l < newPadding; l++)
        {
            fputc(0x00, outptr);
        }

        if ((i + 1) % converted != 0)
        {
            // loop thru *scanline and send each to the file (m)
            for (int m = 0; m < scanlinePixels; m++)
            {
                // Write scanline[m] to outfile
                fwrite(&scanline[m], sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        else
        {
            // reset scanlinePixel to 0
            scanlinePixels = 0;
            // free scanline
            free(scanline);
            // recreate scanline
            scanline = malloc((originalWidth * converted) * sizeof(RGBTRIPLE));
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

bool checkIfBMPFile(char *file)
{
    int length = strlen(file);
    // DO NOT use char[5], data gets persisted.
    char *fileType = malloc((5) * sizeof(char));
    // concat all chars at &file (.bmp)
    strcat(fileType, &file[length - 4]);

    if (strcmp(fileType, ".bmp") == 0)
    {
        free(fileType);
        return true;
    }

    free(fileType);
    return false;
}

bool IsZeroMultipier(char *multiplier)
{
    int length = strlen(multiplier);

    if (length == 1 && isdigit(multiplier[0]))
    {
        return true;
    }
    return false;
}
