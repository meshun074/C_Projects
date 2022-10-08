#include<cs50.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, string argv[])
{
    // Accepts only 2 commandline input
    if(argc != 2)
    {
        printf("Usage ./subtitution key\n");
        return 1;
    }
    //Accept the key length of 26 only
    else if (strlen(argv [1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    //Accept only alphabets and no repetition in the key
    else
    {
        for(int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if(!isalpha(argv[1][i]))
            {
                printf("Key must contain alphabetic characters only\n");
                return 1;
            }
            for(int k = 0, m = strlen(argv[1]); k < m; k++)
            {
                if(i != k)
                {
                    if(tolower(argv[1][k]) == tolower(argv[1][i]))
                    {
                        printf("Key must contain exactly one of the 26 alphabetic characters\n");
                        return 1;
                    }
                }
            }
        }
    }
    // Accept planitext
    string plaintext = get_string("plaintext: ");
    int sub;
    //Convert and print out cipher text
    printf("ciphertext: ");
    for(int g = 0, h = strlen(plaintext); g < h; g++)
    {
        sub = 0;
        //Subtract 65 from upper case alphabetical letters and 97 from lower case alphabetical letters
        //Print it corresponding alphabet from the key to get the cipher text
        if(isalpha(plaintext[g]) && isupper(plaintext[g]))
        {
            sub = (int) plaintext[g] - 65;
            printf("%c",toupper(argv[1][sub]));
        }
        else if(isalpha(plaintext[g]) && islower(plaintext[g]))
        {
            sub = (int) plaintext[g] -97;
            printf("%c", tolower(argv[1][sub]));
        }
        else
        {
            printf("%c",plaintext[g]);
        }
    }
    printf("\n");
    return 0;
}