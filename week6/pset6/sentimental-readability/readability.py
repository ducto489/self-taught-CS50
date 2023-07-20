from cs50 import get_string

text = get_string("Text: ")

letters = sentences = words = 0
i = 0
while True:
    if i >= len(text):
        break
    if text[i].isalpha():
        letters += 1
    elif text[i] in [".", "!", "?"]:
        words += 1
        sentences += 1
        i += 1
    elif text[i] in [',', ';']:
        words += 1
        i += 1
    elif text[i] == ' ':
        words += 1
    i += 1

L = letters * 100 / words
S = sentences * 100 / words

grade = round((0.0588 * L) - (0.296 * S) - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")