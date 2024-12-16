import csv
import sys


def main():
    # Checking for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # Reading database file into a variable
    database = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Reading DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        dna_sequence = file.read()

    # Finding longest match of each STR in DNA sequence
    str_list = list(database[0].keys())[1:]  # 'name' field is skipped
    str_counts = {str_: longest_match(dna_sequence, str_) for str_ in str_list}

    # Checking in database for matching profiles
    for person in database:
        if all(str_counts[str_] == int(person[str_]) for str_ in str_list):
            print(person["name"])
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
