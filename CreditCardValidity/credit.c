#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main()
{
    bool invalid=true;

    do
    {
        long num;
        int lenght;
        long number;
        int cardnum[17];
        int counter=0;
        int sum=0;
        bool lastnum=false;
        number= get_long("enter card number: \n");
        num=number;
        do
        {
            //store card number individually in an arry
            cardnum[counter]=number%10;
            number/=10;
            counter++;

            //store the first two card numbers in num
            if(number/100==0 && number>9)
            {
                num=number;

            }

            //store the last number
            if(number<10)
            {
                cardnum[counter]=number;
            }
        }
        while(number/10!=0);
        //multiply the second numbers by 2
        for (int i=1; i<=counter; i+=2)
        {
            cardnum[i]*=2;
        }
        //add the number
        for(int k=0; k<=counter; k++)
        {
            //if a number is greater than 10 add the individual numbers eg. 12= 1+2
            if(cardnum[k]>9)
            {
                sum+=cardnum[k]/10;
                sum+=cardnum[k]%10;

            }
            else
            {
                sum+=cardnum[k];

            }

        }
        counter++;

        //if the last digit of the sum is not zero or the card numbers length is not equal to 13,15 or 16
        // then the card is valid
        if((counter!=13&&counter!=15&&counter!=16)||sum%10!=0)
        {
            invalid= true;
            printf("INVALID \n");
        }
        else
        {
            if(num==34||num==37)
            {
                invalid=false;
                printf("AMERICAN EXPRESS\n");
            }
            else if(num/10 ==4)
            {
                invalid=false;
                printf("VISA\n");
            }
            else if(num>50 &&num<56)
            {
                invalid=false;
                printf("MASTERCARD\n");
            }
            else
            {
                invalid= true;
                printf("INVALID\n");
            }
        }
    }
    while(invalid);
}