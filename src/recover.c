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

    BYTE buffer[BLOCK_SIZE];
    int i = 0;

    while (fread(buffer, 1, BLOCK_SIZE, input_file) == BLOCK_SIZE)
    {
        // If First 4 Bytes Of Buffer Match JPEG Signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close Previous JPEG File
            if (i != 0)
                fclose(output_file);

            // Create Next JPEG File
            snprintf(output_filename, sizeof(output_filename), "%03i.jpg", i);
            output_file = fopen(output_filename, "w");
            
            // Increment Iteration Counter
            i++;
        }

        // Write Current Buffer To Current JPEG File
        if (i != 0)
            fwrite(&buffer, BLOCK_SIZE, 1, output_file);
    }

    // --------------------------------------------------

    // ------------------ EXIT PROGRAM ------------------

    // Close File Pointers
    fclose(output_file);
    fclose(input_file);

    // Exit Program
    return 0;

    // --------------------------------------------------
}
