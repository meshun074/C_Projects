#include<cs50.h>
#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>

//prototype of functions
int getletters(string text);
int getwords(string text);
int getsentences(string text);

int main()
{
    // get user text
    string text = get_string("Text: ");
    //get the number of letters, word and sentences in the text
    int letters = getletters(text);
    int words = getwords(text);
    int sentences = getsentences(text);
    //printf("%i letter(s)\n%i word(s)\n%i sentence(s)\n",letters, words, sentences);
    //find the average of letter per 100 words and average of sentences per 100 words as l and s
    float l = (100.0/words) *letters;
    float s =(100.0/words) * sentences;
    int index=round(0.0588*l-0.296*s-15.8);
    //print the grade of the text
    if(index<1)
    {
        printf("Before Grade 1\n");
    }
    else if(index>=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",index);
    }
}
//get  number of letters in the text
int getletters(string text)
{
    int counter=0;
    //loop through text snd count only letters
    for (int i=0, n=strlen(text); i<n; i++)
    {
        if((int)toupper(text[i])>64&&(int)toupper(text[i])<91)
        {
            counter++;
        }
    }
return counter;
}

//get number of words
int getwords(string text)
{
    int counter=0;
    //loop through text and count the number of spaces
    for (int i=0, n=strlen(text); i<n; i++)
    {
        if(isspace(text[i]))
        {
            counter++;
        }
    }
    counter++;
    return counter;
}

// get the number of sentences in the text
int getsentences(string text)
{
    int counter=0;
    //loop through text and count the number of punctunctions '.','?','!'
    for (int i=0, n=strlen(text); i<n; i++)
    {
        if((int)text[i]==33||(int)text[i]==46||(int)text[i]==63)
        {
            counter++;
        }
    }
    return counter;
}