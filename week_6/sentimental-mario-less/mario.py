def main():

    # Asking for the height
    height = get_valid_height()

    # Generate the half-pyramid
    for i in range(1, height + 1):
        # Creating the spaces for alignment
        print(" " * (height - i), end="")
        # Printing the blocks
        print("#" * i)


def get_valid_height():
    """Prompt the user for a valid height between 1 and 8, inclusive."""
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
        except ValueError:
            pass
        # If invalid input, reprompt
        print("Please enter a positive integer between 1 and 8.")


if __name__ == "__main__":
    main()
