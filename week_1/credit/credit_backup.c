#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Prompt user for the card number
    string number_input = get_string("Enter Card Number:\n");

    // Get the length of the card number
    int length = strlen(number_input);

    // Arrays to store multiplied and non-multiplied values with their respective lengths
    int multiplied_two_array[strlen(number_input)]; // Stores multiplied values
    int left_values_array[strlen(number_input)];    // Stores non-multiplied values

    // Variables to track array lengths and sums
    int multiplied_two_array_len = 0;
    int sum_multiplied_values = 0;
    int left_values_array_len = 0;
    int total_sum_array_final = 0;

    // Extract the first and second digits of the card number
    int first_digit = (number_input[0] - '0');
    int second_digit = (number_input[1] - '0');
    int index = 0; // Index to track iterations in multiplied_by_two_array

    // Luhn's algorithm

    for (int i = length - 2; i >= 0; i -= 2)
    {
        int number = (number_input[i] - '0') * 2;
        if (number >= 10)
        {
            // If the product is greater than or equal to 10, split the digits
            multiplied_two_array[index] = number % 10; // Insert the units digit
            multiplied_two_array[index + 1] = number / 10; // Insert the tens digit
            index += 2; // Increment the index by 2 for the next insertion
            multiplied_two_array_len += 2; // Increment the array length by 2
        }
        else
        {
            // If the product is less than 10, insert the number directly
            multiplied_two_array[index] = number;
            index++; // Increment the index by 1 for the next insertion
            multiplied_two_array_len++; // Increment the array length by 1
        }
    }

    // Sum the multiplied values
    for (int k = multiplied_two_array_len - 1; k >= 0; k--)
    {
        sum_multiplied_values += multiplied_two_array[k];
    }

    // Extract the non-multiplied values
    for (int l = length - 1, m = 0; l >= 0; l -= 2, m++)
    {
        left_values_array[m] = (number_input[l] - '0');
        left_values_array_len++;
    }

    // Calculate the final sum by adding the sums of multiplied and non-multiplied values
    total_sum_array_final = sum_multiplied_values;
    for (int o = 0; o < left_values_array_len; o++)
    {
        total_sum_array_final += left_values_array[o];
    }

    // Check if the card number satisfies the conditions for VISA, AMEX, or MASTERCARD
    if (first_digit == 4 && (length == 13 || length == 16) && total_sum_array_final % 10 == 0) {
        printf("VISA\n");
    }
    else if ((first_digit == 3 && (second_digit == 4 || second_digit == 7)) && length == 15 && total_sum_array_final % 10 == 0) {
        printf("AMEX\n");
    }
    else if (first_digit == 5 && (second_digit >= 1 && second_digit <= 5) && length == 16 && total_sum_array_final % 10 == 0) {
        printf("MASTERCARD\n");
    }
    else {
        printf("INVALID\n");
    }

    return 0;
}
