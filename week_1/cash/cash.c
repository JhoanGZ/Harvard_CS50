#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_input_number(string valid_input);

int main(void)
{
    bool start;
    float change;

    do
    {
        string input = get_string("What's your change owned in cents:\n");

        bool valid_input = is_input_number(input);

        if (!valid_input)
        {
            start = false;
            printf("No valid input.\n");
            continue;
        }

        // String is converted to an Integer
        change = atoi(input);

        if (change >= 0)
        {
            start = true;
        }
    }
    while (!start);

    // Start process

    // Deduct here the quantity of quarters to return
    float quarter_division = (change / 25);
    int quarter_total_coins = (int) (quarter_division);
    change = change - (quarter_total_coins * 25);

    // Deduct here the quantity of dimes to return
    float dime_division = (change / 10);
    int dime_total_coins = (int) (dime_division);
    change = change - (dime_total_coins * 10);

    // Deduct here the quantity of nickels to return
    float nickels_division = (change / 5);
    int nickels_total_coins = (int) (nickels_division);
    change = change - (nickels_total_coins * 5);

    // Deduct here the quantity of pennies to return
    float penny_division = (change / 1);
    int pennies_total_coins = (int) (penny_division);
    change = change - pennies_total_coins;

    // Sum the total of coins to return
    int total_coins_return =
        (pennies_total_coins + nickels_total_coins + dime_total_coins + quarter_total_coins);
    printf("total: %i\n", total_coins_return);
}

// Check if it's a number =D
bool is_input_number(string valid_input)
{
    // If using the parameter '\0' is how C recognizes a blank as well " \t\n" to recognize if
    // there's any breakline with tab equivalent to an space with a logical 'OR'
    if (valid_input[0] == '\0' || strspn(valid_input, " \t\n") == strlen(valid_input))
    {
        return false;
    }

    for (int i = 0; i < strlen(valid_input); i++)
        if (!isdigit(valid_input[i]) || isblank(valid_input[i]))
        {
            return false;
        }
    return true;
}
