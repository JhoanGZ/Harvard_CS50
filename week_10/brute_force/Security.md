## Security and Power of Computing
Many phones are secured by a four-digit code.
The most simple form of attack would be to brute-force attempt all possible passwords.
There are 10,000 possible passwords when using a four-digit code.
If it takes one guess per second, it will take 10,000 seconds to crack the password.
However, if a programmer creates a program to generate all possible codes, the time required would be minimal. Consider the following code in Python:

```
from string import digits
from itertools import product

for passcode in product(digits, repeat=4):
    print(passcode)

```

It should be quite disconcerting that the code above could take only a few seconds (at most!) to discover your password.
We could improve our security by switching to a four-letter password. This would result in 7,311,616 possible passwords.
Including uppercase and lowercase characters would create over 78 million possibilities.
Consider how we could modify your code to discover these passwords:

```
from string import ascii_letters
from itertools import product

for passcode in product(ascii_letters, repeat=4):
    print(passcode)

```
We could even add the ability to look at all possible eight-digit passwords with letters, numbers, and punctuations:

```
from string import ascii_letters, digits, punctuation
from itertools import product

for passcode in product(ascii_letters + digits + punctuation, repeat=8):
    print(passcode)

```
Expanding to eight characters, including upper and lowercase letters, numbers, and symbols, would result in 6,095,689,385,410,816 possible combinations.

In the digital world, you simply want your password to be better than other peoples’ passwords such that others would be attacked far before you—as you are a much less convenient target.
A downside of using such a long password is the downside of having to remember it.
Accordingly, there are other defenses that could be employed to slow down an attacker. For example, some phone manufacturers lock out those who guess a password incorrectly.

Security is about finding a “sweet spot” between the trade-offs of enhanced security while maintaining convenience.
Password Managers
Password managers can be used to create very challenging passwords and remember them for you.
The probability of a password secured by a password manager being broken is very, very low.
You’d hope that such password managers are secure. However, if one gains access to your password manager, they would have access to all your passwords.
In the end, you are far less likely to be at risk by those you live with—and much more likely to be at risk by the billions of other people on the internet.
As mentioned prior, you can make a decision based on a balance between security and convenience.