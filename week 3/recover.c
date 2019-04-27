#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *createFileName(int fileNumb);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover memorycard\n");
        return 1;
    }

    // remember memcard
    char *memcard = argv[1];

    // open memory card
    FILE *inptr = fopen(memcard, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", memcard);
        return 2;
    }

    // create buffer
    unsigned char *buffer;
    // variable for jpeg file
    char *jpegFile = NULL;
    // jpeg file to write to
    FILE *outptr;
    // counter for jpegs
    int count = 0;
    // byte size of each buffer
    int byteSize;
    // bool for header
    bool headerFound = false;

    buffer = malloc((512) * sizeof(char));
    byteSize = fread(buffer, 1, 512, inptr);

    // while byteSize equals to 512.
    while (byteSize == 512)
    {
        // buffer header is found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            headerFound = true;
            if (jpegFile != NULL)
            {
                //close the previous jpeg file
                fclose(outptr);
            }
            // create name of jpeg file
            jpegFile = createFileName(count);
            // increment count
            count ++;
            // dereference outptr, open and write to name of jpeg file
            outptr = fopen(jpegFile, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", jpegFile);
                return 3;
            }
            // write buffer to jpeg file
            fwrite(buffer, 1, 512, outptr);
        }
        else
        {
            // if headerFound
            if (headerFound)
            {
                //write contents inside file.
                fwrite(buffer, 1, 512, outptr);
            }
        }
        // free buffer
        free(buffer);
        // recreate buffer and read file from memcard
        buffer = malloc((512) * sizeof(char));
        byteSize = fread(buffer, 1, 512, inptr);
    }

    // close infile
    fclose(inptr);
    // success
    return 0;
}

char *createFileName(int fileNumb)
{
    // creating var in stack will be erased once function is executed. WIll NOT BE PERSISTED
    char *fileName = malloc((8) * sizeof(char));
    if (fileNumb < 10)
    {
        sprintf(fileName, "00%i.jpg", fileNumb);
    }
    else
    {
        sprintf(fileName, "0%i.jpg", fileNumb);
    }
    return fileName;
}
