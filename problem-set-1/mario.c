
// Mario pset1
#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // poll user for input
    int n;
    do 
    {
        printf("Please give me an int: ");
        n = GetInt();   
    }
    while (n < 0 || n > 23);

    
    // print pyramid

    for (int i = 0; i < n; i++)
    {
        int count = i + 1;
        int dog = i;
        
        // print spaces
        while (dog < (n - 1) )
        {
            printf(" ");
            dog++;
        }
        
        // print hashes
        while (count >= 0)
        {
            printf("#");
            count--;
        }
        
        // line break
        printf("\n");
        
    }
}    
