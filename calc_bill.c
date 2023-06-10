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

int main(void)
{
    struct Menu snackBar[ITEMS_MAX];
      
    
    FILE *filePointer = fopen("snack_bar.txt", "r");

    if (filePointer == NULL)
    {
        printf ("Cannot open the file!\n");
        return EXIT_ERROR;
    }

    

    return EXIT_SUCCESS;   
}