# c_62_calc_bill

## DESCRIPTION

### LEARNING GOALS

- Practice using structs
- Read items from file into structure
- Write a linear search algorithm

### BACKGROUND

Imagine you’re at the beach and want to order a number of items from the snack bar. You have a limited amount of cash on you, and you want to get a total cost for your items before ordering.

### Implementation Details

Read in the menu items from the `snack_bar.txt` to the `menu` structure. Print out the menu items and their prices, prompting you to keep selecting items until you press enter without typing anything in. Write `get_cost` finction to returns the cost of each item, and `add_items` function to add the chosen menu items. When you are creating a linear search algorithm in `get_cost`, do make sure that it is case insentive.

```bash
snackbar/ $ ./snackbar

Welcome to Beach Burger Shack!
Choose from the following menu to order. Press enter when done.

Burger: $9.50
Vegan Burger: $11.00
Hot Dog: $5.00
Cheese Dog: $7.00
Fries: $5.00
Cheese Fries: $6.00
Cold Pressed Juice: $7.00
Cold Brew: $3.00
Water: $2.00
Soda: $2.00

Enter a food item: burger
Pieces: 2
Enter a food item: fries
Pieces: 1
Enter a food item: 

Your total cost is: $24.00



snackbar/ $ ./snackbar

Welcome to Beach Burger Shack!
Choose from the following menu to order. Press enter when done.

Burger: $9.50
Vegan Burger: $11.00
Hot Dog: $5.00
Cheese Dog: $7.00
Fries: $5.00
Cheese Fries: $6.00
Cold Pressed Juice: $7.00
Cold Brew: $3.00
Water: $2.00
Soda: $2.00

Enter a food item: cold brew
Pieces: 3
Enter a food item: hot dog
Pieces: 5
Enter a food item: 

Your total cost is: $34.00
```

If item is not on the menu print `Invalid item!`:

```bash
snackbar/ $ ./snackbar

Welcome to Beach Burger Shack!
Choose from the following menu to order. Press enter when done.

Burger: $9.50
Vegan Burger: $11.00
Hot Dog: $5.00
Cheese Dog: $7.00
Fries: $5.00
Cheese Fries: $6.00
Cold Pressed Juice: $7.00
Cold Brew: $3.00
Water: $2.00
Soda: $2.00

Enter a food item: cold
Invalid item!
Enter a food item: hot dog
Pieces: 5
Enter a food item: 

Your total cost is: $25.00
```
