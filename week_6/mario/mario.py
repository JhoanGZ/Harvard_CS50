def main():
    # Prompting for the height until a valid input is provided
    height = get_valid_height()

    for i in range(1, height + 1):
        # Print spaces for left alignment
        print(" " * (height - i), end="")

        # Print the left half of the pyramid
        print("#" * i, end="")

        # Print the gap between the pyramids
        print("  ", end="")

        # Print the right half of the pyramid
        print("#" * i)


def get_valid_height():
    while True:
        try:
            # Get user input and convert to an integer
            height = int(input("Height: "))
            if 1 <= height <= 8:
                return height
            else:
                print("Height must be a positive integer between 1 and 8.")
        except ValueError:
            # Catch non-integer inputs
            print("Invalid input. Please enter a positive integer between 1 and 8.")


if __name__ == "__main__":
    main()
