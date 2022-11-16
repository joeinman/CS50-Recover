// -------------------- INCLUDES --------------------

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// --------------------------------------------------

// -------------------- DEFINITIONS --------------------

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

// --------------------------------------------------

int main(int argc, char *argv[])
{
    // ------------ CHECK USER ARGUMENTS ------------

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE.\n");
        return 1;
    }

    // --------------------------------------------------

    // ------------------- OPEN FILE --------------------

    char* input_filename = argv[1];
    FILE* input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        printf("Unable To Open '%s'\n", input_filename);
        return 1;
    }

    // --------------------------------------------------

    // ------------------- CHECK FILE -------------------

    char output_filename[8];
    FILE* output_file = NULL;

    BYTE buffer[512];
    int iteration = 0;

    while (fread(buffer, 1, BLOCK_SIZE, input_file) == BLOCK_SIZE)
    {
        // If start of a new JPEG (0xff 0xd8 0xff 0xe*):
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not first JPEG, close previous
            if (!iteration != 0)
                fclose(output_file);
            
            // Initialise file
            sprintf(output_filename, "%03i.jpg", iteration);
            output_file = fopen(output_filename, "w");
            iteration++;
        }
        
        // If JPEG has been found, write to file
        if (!iteration != 0)
            fwrite(&buffer, 512, 1, output_file);
    }

    // --------------------------------------------------

    // ------------------ EXIT PROGRAM ------------------

    fclose(input_file);
    fclose(output_file);
    return 0;

    // --------------------------------------------------
}