
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
#include <stdlib.h> 
#include "dictionary.h"
#include <ctype.h>
#include <string.h>


    typedef struct node
    {
        bool is_word;
        struct node* children[27];
    } node;
    
    node* root;
    
    node* temp;
    
    int wordCounter = 0;
    
    int a = 97;

    int indexer = 0;
    
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //printf("Checking word: %s\n", word);
    for (int x = 0; x < strlen(word); x++) {
        int letter;
        
        if isalpha(word[x]) {
            letter = tolower(word[x]);
        }
        
        if (word[x] == 39) {
            letter = 123;
        }
        
       // printf("Checking letter: %d\n", letter);
        root = root->children[letter - a];
        
        if (root == NULL) {
            //printf(" root equals false for word: %s\n", word);
            root = temp;
            return false;
            
        }
        else if ((x == (strlen(word) -1)) && (root->is_word == true) ) {
            // printf(" root equals true for word: %s\n", word);
             root = temp;
            return true;
        }
        
        
    }
    
    root = temp;
    return false;
    
    

}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    
    root = malloc (sizeof (node));
    temp = root;

    FILE* fp = fopen(dictionary, "r"); 
    if (fp == NULL) 
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return 1;
    }
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) { // read file character by character
        indexer = 1;
        
        if (isalpha(c)) {
            if (root->children[c - a] == NULL) {
                root->children[c - a] = malloc (sizeof (node));
                //printf("adding a new node child \n");
              // printf("%c\n", c);
            }
            
            root = root->children[c - a];
        }
        
        else if ((c == '\'') && (indexer > 0)) // if character is a letter in a word
        {
            if (root->children[26] == NULL) {
                root->children[26] = malloc (sizeof (node));
                //printf("adding a new node child \n");
              // printf("%c\n", c);
            }
            
            root = root->children[26];
        }
        
        
            
        else if (indexer > 0)  // if reading a word and it's not alphabetical or an apostrophe, end word & reset index to 0
        {
             //printf("before is_word is  %s\n", root->is_word ? "true" : "false");
            root->is_word = true;
            //å printf("after is_word is  %s\n", root->is_word ? "true" : "false");
            wordCounter++;
            indexer = 0;
            root = temp;
            //printf("END WORD\n");
        }
        
    }
    
    
     root = temp;
     return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //printf("%d word counter\n", wordCounter);
    return wordCounter;
    
}

    // void freeNodes(struct node* node)
    // {
    //   int i;
    
    //       for (i=0;i<27;i++)
    //       {
    //          //printf("pos: %d\n", i);
    //          if (node->children[i] != NULL)
    //             printf("%d node child number\n", i);
    //             freeNodes(node->children[i]);
    //             //printf("%d\n", i);
    //       }
    
    //   if (node != NULL)
    //   {
    //       printf("free node"); 
    //       free(node);
    //   }
    
    // }
    
    void freeMemory (struct node* root)
{
    int i;
    for (i = 0; i < 27; i++) 
    {
        //printf("pos: %d\n", i);
        if (root->children[i])
        {
            //printf("node child number %d\n", i);
            freeMemory(root->children[i]);
            
            //printf("%d\n", i);
        }
    }
   // printf("freeing root node %d\n", i);
    
    free(root);
}
    
    
// freeNode(node* currentNode) { 
// First, iterate through all 28 of currentNode's children. 
// For each child, if that child is not null, then call freeNode() on that child. [e.g. freeNode(currentNode[i])] 
// After the loop, free this node itself. free(currentNode) 
// } 

// You'd have to do this for all of the 28 nodes in the start[28] array (assuming they're non-null). 
    
    /** Deallocates memory previously allocated for the TrieNode. */
    // void trieFree(struct node* node) {
    //     trieFreeChildren(node);
    // }
    

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freeMemory(root);
    //free(temp);
    //trieFree(root);
    
    return true;
}


