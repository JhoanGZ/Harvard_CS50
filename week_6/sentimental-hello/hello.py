def main():

    # Asking for the name
    response = get_valid_name()
    print(f"Hello, {response}")


def get_valid_name():
    """Prompting the user for a valid name."""
    while True:
        name = input("What's your name? ")
        if name.strip():
            return name
        else:
            print("Please enter a name, check if you typed it correctly")


if __name__ == "__main__":
    main()
