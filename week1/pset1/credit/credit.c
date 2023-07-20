#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

void Checksum(int secondDigit, int firstDigit);

int main(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);
    if (number < 1000000000000)
    {
        printf("INVALID\n");
        exit(0);
    }
    //printf("%li", number);
    int sum1 = 0, sum2 = 0;
    int secondDigit = 0;
    while (true)
    {
        sum2 = sum2 + (number % 10);
        //printf("sum2:%i, ",sum2);
        if (number < 100 && number > 9)
        {
            //printf("100:%li\nsum1=%i, sum2=%i\n", number, sum1, sum2);
            secondDigit = number % 10;
        }
        if (number < 10)
        {
            break;
        }
        number = number / 10;
        ///////////
        int mod = number % 10;
        if (mod * 2 > 9)
        {
            sum1 = sum1 + (mod * 2) % 10 + 1;//Mod always between 0 and 18
        }
        else
        {
            sum1 = sum1 + mod * 2;
        }
        //printf("sum1:%i\n",sum1);
        if (number < 100 && number > 9)
        {
            //printf("100:%li\nsum1=%i, sum2=%i\n", number, sum1, sum2);
            secondDigit = number % 10;
        }
        if (number < 10)
        {
            break;
        }
        ///////////
        number = number / 10;
    }
    //printf("sum1: %i, sum2: %i\ndau:%li, cuoi:%i\n", sum1, sum2, number, secondDigit);
    if ((sum1 + sum2) % 10 == 0)
    {
        Checksum(number, secondDigit);
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

void Checksum(int firstDigit, int secondDigit)
{
    switch (firstDigit)
    {
        case 3:
            if (secondDigit == 4 || secondDigit == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
            break;
        case 5:
            if (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
            break;
        case 4:
            printf("VISA\n");
            break;
        default:
            printf("INVALID\n");
            break;
    }
}
