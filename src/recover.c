#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check User Arguments
    if (argc != 2)
    {
        printf("Incorrect Syntax.\n");
        return 1;
    }

    // Open File
    char* filename = argv[1];
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Unable To Open '%s'\n", filename);
        return 1;
    }

    // Exit Program
    return 0;
}