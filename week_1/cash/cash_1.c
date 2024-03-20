#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_input_number(string valid_input);
int calculate_quarters(int change);
int calculate_dimes(int change);
int calculate_nickels(int change);
int calculate_pennies(int change);
void total_change(int quarters, int dimes, int nickels, int pennies);

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
    int quarter_total_coins = calculate_quarters(change);
    change -= (quarter_total_coins * 25);
    printf("Quarters: %i\n", quarter_total_coins);

    // Deduct here the quantity of dimes to return
    int dime_total_coins = calculate_dimes(change);
    change -= (dime_total_coins * 10);
    printf("Dimes: %i\n", dime_total_coins);

    // Deduct here the quantity of nickels to return
    int nickels_total_coins = calculate_nickels(change);
    change -= (nickels_total_coins * 5);
    printf("Nickels: %i\n", nickels_total_coins);

    // Deduct here the quantity of pennies to return
    int pennies_total_coins = calculate_pennies(change);
    printf("Pennies: %i\n", pennies_total_coins);

    total_change(quarter_total_coins, dime_total_coins, nickels_total_coins, pennies_total_coins);
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

int calculate_quarters(int change)
{
    // Calculate how many quarters you should give customer
    int quarters = 0;
    while (change >= 25)
    {
        quarters++;
        change -= 25;
    }
    return quarters;
}

int calculate_dimes(int change)
{
    // Calculate how many quarters you should give customer
    int dimes = 0;
    while (change >= 10)
    {
        dimes++;
        change -= 10;
    }
    return dimes;
}

int calculate_nickels(int change)
{
    // Calculate how many quarters you should give customer
    int nickels = 0;
    while (change >= 5)
    {
        nickels++;
        change -= 5;
    }
    return nickels;
}

int calculate_pennies(int change)
{
    // Calculate how many quarters you should give customer
    int pennies = 0;
    while (change >= 1)
    {
        pennies++;
        change -= 1;
    }
    return pennies;
}

void total_change(int quarters, int dimes, int nickels, int pennies)
{
    int total = quarters + dimes + nickels + pennies;
    printf("Total coins: %i\n", total);
}
