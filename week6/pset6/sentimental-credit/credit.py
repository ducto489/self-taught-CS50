from cs50 import get_int
from sys import exit

while True:
    card = get_int("Number: ")
    if card > 0:
        break
if card < 1000000000000:
    print("INVALID")
    exit(0)

string = str(card)
firstDigit = int(string[0])
secondDigit = int(string[1])

# card: 123456789 (this is not a real card)
# total = (8 + 6 + 4 + 2) * 2 + (9 + 7 + 5 + 3 + 1)
number = card
total = 0
for i in range(1, len(string) + 1):
    digit = number % 10
    if i % 2 == 0:
        total += int((digit * 2) / 10) + (digit * 2) % 10
    else:
        total += digit
    number = int(number / 10)

if total % 10 != 0:
    print("INVALID")
    exit(0)

if firstDigit == 4:
    print("VISA")
elif firstDigit == 3 and secondDigit in [4, 7]:
    print("AMEX")
elif firstDigit == 5 and secondDigit in [1, 2, 3, 4, 5]:
    print("MASTERCARD")
else:
    print("INVALID")