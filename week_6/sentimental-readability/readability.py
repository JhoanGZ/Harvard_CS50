import re


def main():
    # Prompt the user for input
    text = input("Text: ")

    # Count letters, words, and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Coleman-Liau index Calculation
    index = calculate_index(letters, words, sentences)

    print_grade_level(index)


def count_letters(text):
    """Count the number of letters in the text."""
    return sum(1 for char in text if char.isalpha())


def count_words(text):
    """Count the number of words in the text."""
    return len(text.split())


def count_sentences(text):
    """Count the number of sentences in the text."""
    return sum(1 for char in text if char in '.!?')


def calculate_index(letters, words, sentences):
    """Calculate the Coleman-Liau index."""
    L = (letters / words) * 100  # Average number of letters per 100 words
    S = (sentences / words) * 100  # Average number of sentences per 100 words
    return 0.0588 * L - 0.296 * S - 15.8  # Calculating result


def print_grade_level(index):
    """Print the grade level based on the Coleman-Liau index."""
    grade = round(index)
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()
