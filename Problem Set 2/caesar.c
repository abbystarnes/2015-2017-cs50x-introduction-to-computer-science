#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
// get key
    if (argv[1] == NULL)
    {
        printf("Incorrect input. Please rerun caesar. \n");
        return 1;
    }
    // printf("Please supply a positive integer: \n");
    int k = atoi(argv[1]);
    // printf("%d\n", k);
    if (argc != 2 || k <= 0)
    {
        printf("Incorrect input. Please rerun caesar. \n");
        return 1;
    }
    else
    {   
        
        string p = GetString();
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            if (p[i] > 64 && p[i] < 91)
            {
                printf("%c", ((p[i] - 65 + k) % 26) + 65);
            }
            
            // else if
            else if (p[i] > 96 && p[i] < 123)
            {
                printf("%c", ((p[i] - 97 + k) % 26) + 97);
            } 
            
            else
            {
                printf("%c", (p[i]));
            }
 
        }
        printf("\n");
        return 0;
    }
}
   
    
    // shift one letter
    // sort letters from spaces and punctuation
    
    
    // prompt user for non-negative integer
    // if input is not acceptable, prompt to start over
        // 1. argc > 2
        // 2. k < 0 or = 0 (including letters)
            // string k = argv[1];
            // int k = atoi(argv[1]); converts string to int
        // return 1; signifying errors
// get plain text
    // prompt user for plain text (get string)
// encipher
    // for (int i = 0, n = strlen(p); i < n; i++)
// {printf("%c", p[i]);}
// one character
// entire plain text
// print cipher text
