#include <cs50.h>
#include <stdio.h>

#define CHARS_MAX 30
#define ITEMS_MAX 30
#define EXIT_ERROR 1
#define EXIT_SUCCESS 0

struct Menu
{
    char    Item[CHARS_MAX];
    float   Price;
};

int read_file_by_delimiter(FILE *fP, char output[CHARS_MAX], int max_char_read, int delimiter);

int main(void)
{
    struct Menu snackBar[ITEMS_MAX];
      
    
    FILE *filePointer = fopen("snack_bar.txt", "r");

    if (filePointer == NULL)
    {
        printf ("Cannot open the file!\n");
        return EXIT_ERROR;
    }

    char word[CHARS_MAX];

    read_file_by_delimiter(filePointer, word, CHARS_MAX, ':');

    printf ("%s\n", word);
    

    return EXIT_SUCCESS;   
}

// Read word from file from actual position up to the given delimiter or EOF
int read_file_by_delimiter(FILE *fP, char output[CHARS_MAX], int max_char_read, int delimiter)
{
    // read file by delimiter
    int i = 0;

    int read_char = fgetc(fP);

    while (read_char != EOF && read_char != delimiter && i < max_char_read)
    {
        output[i++] = read_char;

        read_char = fgetc(fP);
    }

    // Put null character at end of the string
    output[i] = '\0';

    return EXIT_SUCCESS;
}