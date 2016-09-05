/*****************************************************************************
 * factorial.c
 * Matthew Chartier
 * CS 50/CSCI E-52
 * Fall 2010
 *
 * Get a number n from the user and compute n-factorial using a loop.
 *****************************************************************************/

#include <stdio.h>
#include <cs50.h>

int
main (int argc, char *argv[])
{
    printf("Your number: ");
    int n = GetInt();
    int fact_n = 1;
    
    while(n > 1)
    {
        fact_n = fact_n * n;
	n--;
    }
    
    printf("Factorial: %d\n", fact_n);

}
