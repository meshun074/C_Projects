#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    //if commandline argument is not equal to 2 print an error message
    if(argc!=2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //if an element of the commandline argument is not a digit print an error message
    for (int i = 0,n = strlen(argv[1]); i < n; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    //accept user text and convert commandline argument to an integer
    string plaintext = get_string("plaintext: ");
    int key = atoi(argv[1]);
    //print cipher text by rotating each character by a given key ignoring punctuations an empty spaces
    printf("ciphertext: ");
    for (int i = 0,n = strlen(plaintext); i < n; i++)
    {
        int cipher = 0;
        if(isalpha(plaintext [i]))
        {
            cipher = key % 26 + (int)plaintext[i];
            // if the cipher integer exceed ascii character range start from begining depending on whether is lower or uppercase
            if(isupper(plaintext [i]) && cipher > 90)
            cipher = cipher - 90 + 64;
            else if(islower(plaintext [i]) && cipher > 122)
            cipher = cipher - 122 + 96;

            printf("%c", cipher);
        }
        else
        printf("%c", plaintext[i]);
    }
    printf("\n");
    return 0;
}