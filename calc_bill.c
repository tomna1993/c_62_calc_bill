#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define CHARS_MAX 30
#define ITEMS_MAX 30
#define EXIT_ERROR 1
#define EXIT_SUCCESS 0

struct Menu
{
	char    Item[CHARS_MAX];
	float   Price;

	char    UserItem[CHARS_MAX];
};

int read_file_by_delimiter(FILE *fP, char output[CHARS_MAX], int max_char_read, int delimiter);
int load_file_into_struct(FILE *fP, struct Menu menu_struct[ITEMS_MAX], int max_items_to_read, int max_char_to_read);
float atoi_float(char number_text[CHARS_MAX]);
int print_struct(struct Menu menu_struct[ITEMS_MAX], int length);
float ask_user_for_items(struct Menu menu[ITEMS_MAX], int max_items_to_read, int max_string_length);
float search_item_in_menu(struct Menu menu[ITEMS_MAX], char item[CHARS_MAX], int items_in_menu, int max_string_length);

int main(void)
{
	struct Menu snackBar[ITEMS_MAX];
	
	// Open file to read
	FILE *filePointer = fopen("snack_bar.txt", "r");

	if (filePointer == NULL)
	{
		printf ("Cannot open the file!\n");
		return EXIT_ERROR;
	}

	const int num_of_items = load_file_into_struct(filePointer, snackBar, ITEMS_MAX, CHARS_MAX);

	// Close file
	fclose(filePointer);

	// Print welcome screen and menu items
	printf ("\nWelcome to Beach Burger Shack!\n");
	printf ("Choose from the following menu to order. Press enter when done.\n\n");  
	print_struct(snackBar, num_of_items);
	printf ("\n\n");

	printf ("\nYour total cost is: $%.2f\n", ask_user_for_items(snackBar, num_of_items, CHARS_MAX));

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
		printf ("%s: $%.2f\n", menu_struct[i].Item, menu_struct[i].Price);
	}

	return EXIT_SUCCESS;
}

// Ask user for item and find it int the menu and return its price
float ask_user_for_items(struct Menu menu[ITEMS_MAX], int max_items_to_read, int max_string_length)
{
	int i = 0;
	float bill = 0.0;

	// Prompt user for item and piece
	do
	{
		strcpy(menu[i].UserItem, get_string("Enter a food item: "));

		// In case of no input (user hits ENTER) return with the bill
		if (strlen(menu[i].UserItem) == 0)
		{
			break;
		}    

		// Find the item from user input in menu and return its price
		float price = search_item_in_menu(menu, menu[i].UserItem, max_items_to_read, max_string_length);

		if (price == 0.0)
		{
			printf ("Invalid item!\n");
			continue;
		}

		i++;

		// Calculate bill	
		bill += get_float("Pieces: ") * price;
	} 
	while (i <= max_items_to_read);

	return bill;
}

// Search item in menu and return the price of the item
float search_item_in_menu(struct Menu menu[ITEMS_MAX], char item[CHARS_MAX], int items_in_menu, int max_string_length)
{
	char menu_item[max_string_length];
	char choosen_item[max_string_length];

	int j = 0;

	// Convert choosen item letters into lowercase latters
	for (int length = strlen(item); j < length; j++)
	{
		choosen_item[j] = tolower(item[j]);
	}
	choosen_item[j] = '\0';

	for (int i = 0; i <= items_in_menu; i++)
	{
		// Convert menu item letters into lowercase letters
		j = 0;
		for (int length = strlen(menu[i].Item); j < length; j++)
		{
			menu_item[j] = tolower(menu[i].Item[j]);
		}
		menu_item[j] = '\0';

		// Compare user and menu item and return price
		if (strcmp(menu_item, choosen_item) == 0)
		{
			return menu[i].Price;
		}
	}

	// No price means no item in menu
	return 0.0;
}