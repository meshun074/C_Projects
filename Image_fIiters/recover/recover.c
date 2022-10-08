#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //check command line input
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open forensic image
    FILE *file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Fail to open %s\n", argv[1]);
        return 1;
    }
    char filename[] = "000.jpg";
    int counter = 0;
    FILE *picture = fopen(filename, "w");
    if(picture == NULL)
    {
        printf("Fail to open %s\n", filename);
        return 1;
    }

    //define 8 bit unsigned integer as byte
    typedef uint8_t byte;
    //Allocate a memory of 512 byte as block
    //note block[0] == *(block + 0)
    byte block[512];
    while(1)
    {
        fread(block, sizeof(block), 1, file);
        //checking which the block of 512 bytes begin with 0xff 0xd8 0xff
        //And the four byte is 0xe0 - 0x ef
        if(block[0] == 255 && block[1] == 216 && block[2] == 255 && block[3] > 223 && block[3] < 240)
        {
            //close picture file if we have opened a picture file
            if(counter > 0)
            {
                fclose(picture);
                sprintf(filename, "%03d.jpg", counter);
                picture = fopen(filename, "w");
            }
            // print a file name format into the string filename
            counter++;
        }
        if(feof(file))
        {
            fclose(picture);
            break;
        }
        //write to picture file only if we have opened it
        if(counter > 0)
        {
            fwrite(block, sizeof(block), 1, picture);
        }
    }
    //*/
    fclose(file);
}