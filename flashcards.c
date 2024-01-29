#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// for file reading
#define MAX_LINES 100
#define MAX_LEN 200

struct fileContents
{
    int len;
    char **contents;
};

typedef struct fileContents Struct;

// function definitions
struct fileContents readFile(char *filename);
typedef struct fileContents Struct;

int main()
{

    printf("Which header file would you like to test?\n");
    printf("string.h :  0\n");
    printf("stdlib.h  :  1\n");
    printf("ctype.h  :  2\n");

    char *filename = (char *)malloc(20);
    int in = 0;
    scanf("%d", &in);

    if (in == 0)
    {
        strncpy(filename, "data/string.txt\0", 20);
    }
    else if (in == 1)
    {
        strncpy(filename, "data/stdlib.txt\0", 20);
    }
    else if (in == 2)
    {
        strncpy(filename, "data/ctype.txt\0", 20);
    }

    struct fileContents data = readFile(filename);

    for (int i = 0; i < data.len; i += 2)
    {
        printf("%s\n", data.contents[i]);
        printf("%s\n", data.contents[i + 1]);
    }
    return 0;
}

struct fileContents readFile(char *filename)
{
    // create memory for outer
    char **fileContents = malloc(MAX_LINES * sizeof(char *));
    // create memory for inner
    for (int i = 0; i < MAX_LINES; i++)
    {
        fileContents[i] = malloc(MAX_LEN * sizeof(char));
    }

    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        printf("file machine broke");
        // return 1;
    }

    int line = 0;

    while (!feof(fptr) && !ferror(fptr))
    {
        if (fgets(fileContents[line], MAX_LEN, fptr) != NULL)
        {
            line++;
        }
    }

    fclose(fptr);
    // return
    struct fileContents contents;
    contents.contents = fileContents;
    contents.len = line;
    printf("lines number = %d\n", line);
    return contents;
}
