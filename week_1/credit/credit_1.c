#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populateMultipliedArray(int multiplied_two_array[], int *multiplied_two_array_len,
                             string number_input, int length);
int calculateSumMultiplied(int multiplied_two_array[], int multiplied_two_array_len);
void populateLeftValuesArray(int left_values_array[], int *left_values_array_len,
                             string number_input, int length);
int calculateTotalSum(int sum_multiplied_values, int left_values_array[],
                      int left_values_array_len);

int main(void)
{
    string number_input = get_string("Enter Card Number:\n");

    int length = strlen(number_input);
    int multiplied_two_array[length]; // Setting the array length according to input number where
                                      // the multiplied values will be saved
    int left_values_array[length]; // Setting the array length according to input number where the
                                   // rest of values will be saved
    int multiplied_two_array_len = 0;
    int left_values_array_len = 0;
    int first_digit = (number_input[0] - '0');
    int second_digit = (number_input[1] - '0');

    // Populate the array with multiplied values
    populateMultipliedArray(multiplied_two_array, &multiplied_two_array_len, number_input, length);

    printf("Multiplied by 2 Array: ");
    for (int i = 0; i < multiplied_two_array_len; i++)
    {
        printf("%i ", multiplied_two_array[i]);
    }
    printf("\n");

    // Calculate the sum of multiplied values
    int sum_multiplied_values =
        calculateSumMultiplied(multiplied_two_array, multiplied_two_array_len);
    // printf("Sum of multiplied values: %i\n", sum_multiplied_values);

    // Populate the array with remaining values
    populateLeftValuesArray(left_values_array, &left_values_array_len, number_input, length);

    // printf("Left values array: ");
    for (int i = 0; i < left_values_array_len; i++)
    {
        printf("%i ", left_values_array[i]);
    }
    // printf("\n");

    // Calculate the final sum
    int total_sum_array_final =
        calculateTotalSum(sum_multiplied_values, left_values_array, left_values_array_len);
    // printf("Total sum final: %i\n", total_sum_array_final);

    // Check if the first digit of the card number is '4' for VISA
    if (first_digit == 4 && (length == 13 || length == 16) && total_sum_array_final % 10 == 0)
    {
        printf("VISA\n");
    }
    // Check if the first two digits of the card number are '34' or '37' for AMEX
    else if ((first_digit == 3 && (second_digit == 4 || second_digit == 7)) && length == 15 &&
             total_sum_array_final % 10 == 0)
    {
        printf("AMEX\n");
    }
    // Check if the first digit of the card number is '5' and the second digit is between '1' and
    // '5' for MASTERCARD
    else if (first_digit == 5 && (second_digit >= 1 && second_digit <= 5) && length == 16 &&
             total_sum_array_final % 10 == 0)
    {
        printf("MASTERCARD\n");
    }
    // If none of the above conditions are met, the card is invalid
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// Function to populate the array with multiplied values
void populateMultipliedArray(int multiplied_two_array[], int *multiplied_two_array_len,
                             string number_input, int length)
{
    int index = 0; // to track iterations in multiplied_two_array
    for (int i = length - 2; i >= 0; i -= 2)
    {
        int number = (number_input[i] - '0') * 2;
        if (number >= 10)
        {
            multiplied_two_array[index] = number % 10;     // Inserts the units digit
            multiplied_two_array[index + 1] = number / 10; // Inserts the tens digit
            index += 2;                     // Increments the index by 2 for the next insertion
            *multiplied_two_array_len += 2; // Increments the array length by 2
        }
        else
        {
            multiplied_two_array[index] = number; // Inserts the number directly
            index++;                       // Increments the index by 1 for the next insertion
            (*multiplied_two_array_len)++; // Increments the array length by 1
        }
    }
}

// Function to calculate the sum of multiplied values
int calculateSumMultiplied(int multiplied_two_array[], int multiplied_two_array_len)
{
    int sum_multiplied_values = 0;
    for (int k = multiplied_two_array_len - 1; k >= 0; k--)
    {
        sum_multiplied_values += multiplied_two_array[k];
    }
    return sum_multiplied_values;
}

// Function to populate the array with remaining values
void populateLeftValuesArray(int left_values_array[], int *left_values_array_len,
                             string number_input, int length)
{
    for (int l = length - 1, m = 0; l >= 0; l -= 2, m++)
    {
        left_values_array[m] = (number_input[l] - '0');
        (*left_values_array_len)++;
    }
}

// Function to calculate the final sum
int calculateTotalSum(int sum_multiplied_values, int left_values_array[], int left_values_array_len)
{
    int total_sum_array_final = sum_multiplied_values;
    for (int o = 0; o < left_values_array_len; o++)
    {
        total_sum_array_final += left_values_array[o];
    }
    return total_sum_array_final;
}
