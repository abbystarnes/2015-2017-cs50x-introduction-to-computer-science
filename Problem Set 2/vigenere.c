#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    if (argv[1] == NULL)    
    {
        printf("Incorrect input, no second argument. Please rerun vigenere. \n");
        return 1;
    }
   
    if (argc != 2)
    {
        printf("Incorrect input, wrong number of arguments. Please rerun vigenere. \n");
        return 1;
    }
    
    
    string keyword = argv[1];
    int keyLength = strlen(keyword);
    // string keyword2 = array[];
    
    for (int i = 0, n = keyLength; i < n; i++) 
    {
         if (isalpha(keyword[i]))
         {
           // printf("letter is alphabetical. \n");
         }
         
         else 
         {
            printf("Input is not alphabetical. Please rerun vigenere. \n");
            return 1;
         }
    }
    
    
    for (int i = 0, n = keyLength; i < n; i++)
    {
            keyword[i] = tolower(keyword[i]) - 'a';
           // printf("%d", (keyword[i]));
       /* if (islower(keyword[i]))
        {
            keyword[i] = keyword[i] - 97;
            printf("%d", (keyword[i]));
        }
        
        else if (isupper(keyword[i]))
        {
            keyword[i] = keyword[i] - 65;
            printf("%d", (keyword[i]));
        }  */      
                
    }
    
   // printf("%s\n", keyword);
    //printf("\n");
    
    string plaintext = GetString();
    int j =0;
    //int j = counter % (keyLength);

    for (int i=0, n = strlen(plaintext); i < n; i++)
    {

        if (isupper(plaintext[i]))
        {
            printf("%c", ((((plaintext[i])-65) + ((keyword[j%(keyLength)])))%26) +65 );
            j ++;
        }
        
        else if (islower(plaintext[i]))
        {
            printf("%c", ((((plaintext[i])-97) + ((keyword[j%(keyLength)])))%26) +97);
            j ++;
        }
        
        else 
        {
            printf("%c", plaintext[i]);
        }
        
    }
    printf("\n");
    return 0;
}    


 
