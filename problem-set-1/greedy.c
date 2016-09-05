// Greedy pset1
#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
    float amount;
    int count = 0;
    int roundedCents;
    
    // poll user for input
    do
    {
        printf("Please give an amount in dollars:");
        amount = GetFloat();
        
        /*The amount in dollars*/
        
        float cents = amount * 100;
        /*The amount in cents*/
        
        roundedCents = (long) (cents + 0.5);
        /*The amount in rounded cents*/
      
    }while (amount < 0);

    // count coins needed to make change
    while (roundedCents >= 25) 
    {
        roundedCents -= 25;
        count++;
    }
    ;

    while(roundedCents >= 10) 
    {
        roundedCents -= 10;
        count++;
    }
    ;
  
    while(roundedCents >= 5)
    {
        roundedCents -= 5;
        count++;
    }
    ;

    while(roundedCents >= 1)
    {
        roundedCents -= 1;
        count++;
    }
    ;
 
    // print coins needed to make change
    printf("%d\n", count);
    
   
}    
