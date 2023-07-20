#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

bool checkKey(int argc, string argv[]);
string encipher(string text, string key);

char ARRAY[2][26] = {{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}, {}};

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (checkKey(argc, argv))
    {
        return 1;
    }
    string plainText = get_string("plaintext:  ");
    string cipherText = encipher(plainText, argv[1]);
    printf("ciphertext: %s\n", cipherText);
    return 0;
}

bool checkKey(int argc, string argv[])
{
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int count = 0, length = strlen(argv[1]); count < length; count++)
    {
        if (!(isalpha(argv[1][count])))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        if (islower(argv[1][count]))
        {
            argv[1][count] = toupper(argv[1][count]);
        }
        int ordinal = (int)argv[1][count] - 65;
        if (ARRAY[1][ordinal] == '1')
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        else
        {
            ARRAY[1][ordinal] = '1';
        }
    }
    return 0;
}

string encipher(string text, string key)
{
    for (int count = 0, length = strlen(text); count < length; ++count)
    {
        if (isalpha(text[count]))
        {
            bool isLowerCase = islower(text[count]);
            text[count] = toupper(text[count]);
            int ordinal = text[count] - 65;
            text[count] = key[ordinal];
            if (isLowerCase)
            {
                text[count] = tolower(text[count]);
            }
        }
    }
    return text;
}
