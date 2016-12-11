/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <ctype.h>

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    typedef struct node
    {
        bool is_word;
        struct node* children[27];
    } node;
    
    node* root = malloc(sizeof(node));
    
    int index = 0;
    int words = 0;
    char word[LENGTH+1]; // make an array called word with room for letters plus one 
    FILE* fp = fopen(dictionary, "r"); // file pointer fp points to text, open it for reading
    if (fp == NULL) // if the file is null/0, then stop running program and return error
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return 1;
    }
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        
        if (isalpha(c) || (c == '\'' && index > 0)) // if character is alphabetical, or it is an apostrophe
        {
            // append character to word
            word[index] = c; //write character to word array
            index++; //advance word array index
            // write first letter to head node array
            // if next node array exists, write next letter to next node array
            // else create next node array and write next letter to it
            
        }
        
        else if (index > 0)  // if there's a word
        {
            // terminate current word
            word[index] = '\0';  // end current word
            
            

            // update counter 
            words++; //update word counter to reflect new word

            printf("%s\n", word);

            // prepare for next word
            index = 0;
        }
        
    }

    
    
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
