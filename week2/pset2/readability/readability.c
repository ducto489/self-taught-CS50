#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void countLetterAndWord(string text);

int cLetter = 0, cWord = 0, cSentences = 0;

int main(void)
{
	string text = get_string("Text: ");
	//printf("%s\n", text);
    countLetterAndWord(text);
	//printf("cL:%i, cW:%i, cS:%i\n", cLetter, cWord, cSentences);

	//Coleman-Liau index
	long double L, S;
	L = ((long double)cLetter * 100) / (long double)cWord;
	S = ((long double)cSentences * 100) / (long double)cWord;
	int index = round((0.0588 * L) - (0.296 * S) - 15.8);
	if (index < 1)
	{
		printf("Before Grade 1\n");
	}
	else if (index >= 16)
	{
		printf("Grade 16+\n");
	}
	else
	{
	printf("Grade %i\n", index);
	}
	return 0;
}

void countLetterAndWord(string text)
{
	for (int count = 0, length = strlen(text); count < length; ++count)
	{
		if (isalpha(text[count]))
		{
			cLetter++;
		}
		else if (text[count] == '!' || text[count] == '?' || text[count] == '.' || text[count] == ',' || text[count] == ';')
		{
			cWord++;
			if (text[count] != ',' && text[count] != ';')
			{
				cSentences++;
			}
			count++;
		}
		else if (text[count] == ' ')
		{
			cWord++;
		}
	}
}
