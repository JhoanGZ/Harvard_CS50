import re


def main():
    # Prompt the user for a credit card number
    card_number = input("Number: ")

    # Validate the card number
    if not card_number.isdigit():
        print("INVALID")
    elif is_valid(card_number):
        print_card_type(card_number)
    else:
        print("INVALID")


def is_valid(card_number):
    """Check if the card number is valid using Luhn's Algorithm."""
    total = 0
    reversed_digits = card_number[::-1]

    for i, digit in enumerate(reversed_digits):
        n = int(digit)
        if i % 2 == 1:  # Every second digit (0-indexed)
            n *= 2
            if n > 9:
                n -= 9
        total += n

    return total % 10 == 0


def print_card_type(card_number):
    """Determine and print the card type based on number patterns."""
    if re.match(r"^3[47]\d{13}$", card_number):
        print("AMEX")
    elif re.match(r"^5[1-5]\d{14}$", card_number):
        print("MASTERCARD")
    elif re.match(r"^4(\d{12}|\d{15})$", card_number):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
