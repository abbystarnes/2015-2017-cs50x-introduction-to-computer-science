#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// argc = # strings in command line
// argv = array containing strings in command line
int main(int argc, string argv[])
{
    string yourName = GetString();
    // printf("%s\n", yourName);
    if (yourName != NULL)
    {
        printf("%c", toupper(yourName[0]));
        for (int i = 0, n = strlen(yourName); i < n; i++)
        {
            if (isspace(yourName[i]))
            { 
                printf("%c", toupper(yourName[i + 1]));
            }
        }
        printf("\n");
    }
}


 
