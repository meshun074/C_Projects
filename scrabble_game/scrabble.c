#include<ctype.h>
#include<cs50.h>
#include<stdio.h>
#include<string.h>

//Points assigned to each letter of the alphabet
int POINTS[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
int compute_score(string word);

int main(void)
{
    //Get input words from both players
    string word1=get_string("Player 1: ");
    string word2=get_string("Player 2: ");

    // score both word
    int score1= compute_score(word1);
    int score2= compute_score(word2);
    //print the player with higher as winner or tie if both score are equal
    if(score1>score2)
    {
        printf("Player 1 wins! %i %i\n",score1 ,score2);

    }
    else if(score2>score1)
    {
        printf("Player 2 wins! %i %i\n",score1 ,score2);

    }
    else
    {
        printf("Tie! %i %i\n",score1 ,score2);

    }

}

// compute score
int compute_score(string word)
{
int score=0;
for(int i =0, n= strlen(word); i<n; i++ )
{
    //add o if the letter is not alphabet
    if((int)word[i]<65&&(int)word[i]>90||(int)word[i]<97&&(int)word[i]>122)
    {
        score+=0;

    }
    // convert letter to uppercase and then to integer
    // subtract 65 from the integer for A to have index 0, B index etc.
    // Add the corresponding score of the character
    else
    {
        word[i]= toupper(word[i]);
        score+=POINTS[(int)word[i]-65];

    }
}
return score;
}