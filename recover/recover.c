#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file. \n");
        return 1;
    }
    FILE *output = NULL;
    int files = 0;
    char jpgname [8];
    uint8_t block[512];
    while (fread(&block,512, 1, input) == 1)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] >= 0xe0 && block[3] <= 0xef))
        {
            if (output != NULL)
            {
                fclose(output);
            }
            files ++;
            sprintf(jpgname, "%03d.jpg", files);
            output = fopen(jpgname, "w");
        }
        if (output != NULL)
        {
            fwrite(&block, 512, 1, output);
        }
    }
    fclose(input);
    fclose(output);
}