# Substitution Cipher

This program implements a substitution cipher, a type of encryption where each letter in the plaintext is replaced by a corresponding letter from a key. The key provided must be a 26-character set representing the alphabet.

## Usage

./substitution key

## Input

The program takes one command-line argument:
- `key`: A string of 26 characters representing the substitution cipher key.

## Output

The program prompts the user for plaintext input and outputs the corresponding ciphertext.

## Constraints

- The key must consist of exactly 26 characters.
- The key must contain only alphabetic characters (no spaces or punctuation marks).

## Implementation Details

- The program verifies the validity of the provided key, ensuring it meets the specified requirements.
- Each character in the plaintext is replaced by its corresponding character in the key, preserving case.
- Non-alphabetic characters in the plaintext are left unchanged.
- The resulting ciphertext is printed to the console.
