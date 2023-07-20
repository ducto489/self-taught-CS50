#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover IMAGE\n");
        return 1;
    }
    char *filein = argv[1];
    // char *outfile = ;
    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    BYTE buffer[513];
    int i = 0;
    FILE *img = NULL;
    while (fread(buffer, 1, 512, file) == 512)
    {
        // Check the header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close file was writing
            if (i != 0)
            {
                fclose(img);
            }
            char filename[8] = {};
            sprintf(filename, "%03i.jpg", i++);
            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }
    return 0;
}