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
int load_file_into_struct(FILE *fP, struct Menu menu_struct[ITEMS_MAX], int max_items_to_read, int max_char_to_read);
float atoi_float(char number_text[CHARS_MAX]);
int print_struct(struct Menu menu_struct[ITEMS_MAX], int length);

int main(void)
{
    struct Menu snackBar[ITEMS_MAX];
      
    
    FILE *filePointer = fopen("snack_bar.txt", "r");

    if (filePointer == NULL)
    {
        printf ("Cannot open the file!\n");
        return EXIT_ERROR;
    }

    const int num_of_items = load_file_into_struct(filePointer, snackBar, ITEMS_MAX, CHARS_MAX);

    print_struct(snackBar, num_of_items);

    return EXIT_SUCCESS;   
}

int load_file_into_struct(FILE *fP, struct Menu menu_struct[ITEMS_MAX], int max_items_to_read, int max_char_to_read)
{
    int i = 0;

    for (; i < max_items_to_read; i++)
    {
        read_file_by_delimiter(fP, menu_struct[i].Item, max_char_to_read, ':');

        if (menu_struct[i].Item[0] == '\0')
        {
            break;
        }

        char number_text[max_char_to_read];
        read_file_by_delimiter(fP, number_text, max_char_to_read, '\n');

        // Convert string number to float
        menu_struct[i].Price = atoi_float(number_text);
    }

    // return the number of items read from the file until we reached EOF
    return i;
}

// Read word from file from actual position up to the given delimiter or EOF
int read_file_by_delimiter(FILE *fP, char output[CHARS_MAX], int max_char_read, int delimiter)
{
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

// Convert number text to decimal number
float atoi_float(char number_text[CHARS_MAX])
{
    float integer = 0;
    float decimal = 0;
    float sign = 1.0;

    int i = 0;


    // Remove any whitespace
    while ( number_text[i] == ' ' ||
            number_text[i] == 't' ||
            number_text[i] == '\n')
    {
        i++;
    }

    // Remove currency symbol
    if (number_text[i] == '$')
    {
        i++;
    }

    if (number_text[i] == '-' || number_text[i] == '+')
    {
        if (number_text[i] == '-')
        {
            sign = -1.0;
        }
    }

    // Convert integer part
    while (number_text[i] != '\0' && number_text[i] != '.')
    {
        integer = (integer * 10) + (number_text[i] - '0');
        i++;
    }

    // Convert decimal part
    if (number_text[i++] == '.')
    {
        float power_of_ten = 10.0;

        while (number_text[i] != '\0')
        {
            decimal = decimal + (number_text[i] - '0') / power_of_ten;
            i++;

            power_of_ten *= 10.0;
        }
    }
   
    return (integer + decimal) * sign;
}

int print_struct(struct Menu menu_struct[ITEMS_MAX], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf ("%s: %.2f\n", menu_struct[i].Item, menu_struct[i].Price);
    }

    return EXIT_SUCCESS;
}