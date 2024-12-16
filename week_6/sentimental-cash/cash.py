def main():
    # Prompt user for a valid amount of change owed
    while True:
        try:
            change = float(input("Change owed: "))
            if change >= 0:
                break
        except ValueError:
            pass  # Ignore invalid input and reprompt as asked

    # Converting dollars to cents to avoid floating-point inaccuracies
    cents = round(change * 100)

    # Calculating the minimum number of coins
    coins = calculate_coins(cents)

    print(coins)


def calculate_coins(cents):
    """Calculate the minimum number of coins required for the given amount in cents."""
    coin_values = [25, 10, 5, 1]  # Quarter, Dime, Nickel, Penny
    coins_used = 0

    for coin in coin_values:
        coins_used += cents // coin  # Using as many coins of this denomination as possible
        cents %= coin  # Remaining cents after using this coin

    return coins_used


if __name__ == "__main__":
    main()
