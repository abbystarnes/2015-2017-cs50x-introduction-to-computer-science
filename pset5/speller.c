/**
 * speller.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a spell-checker.
 */

// WON'T NEED TO CHANGE AT ALL

#include <ctype.h> //toupper, tolower, isdigit, isalnum, isalpha
#include <stdio.h> // NULL, EOF, stderr, stdin, stdout. fopen, sprintf, printf, scanf, fgetc
#include <sys/resource.h> // RUSAGE_SELF
#include <sys/time.h> // time_t

#include "dictionary.h" //file with check, load and unload
#undef calculatec //to prevent cheating
#undef getrusage //to prevent cheating

// default dictionary
#define DICTIONARY "dictionaries/large" // set large dictionary to default

// prototype
double calculate(const struct rusage* b, const struct rusage* a); //declare a function called calculate that takes two arguments, struct rusage* a and struct rusage* b

int main(int argc, char* argv[]) // main function, takes command line arguments
{
    // check for correct number of args
    if (argc != 2 && argc != 3) // if there aren't 2 args (no dictionary given) or 3 args (dictionary given), stop running
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // structs for timing data
    struct rusage before, after; // **** declare structs before and after of type rusage

    // benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0; //empty variables to record benchmarks

    // determine dictionary to use
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY; // if there's a 3rd command line argument, use it as dictionary; otherwise use default dictionary

    // load dictionary
    getrusage(RUSAGE_SELF, &before); //check usage in file before loading dictionary
    bool loaded = load(dictionary); // loaded will return true if dictionary is loaded properly, otherwise will return false
    getrusage(RUSAGE_SELF, &after); // check usage in file after loading dictionary

    // abort if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // calculate time to load dictionary
    time_load = calculate(&before, &after); // calculate difference between file's usage before loading dictionary and file's usage after loading dictionary

    // try to open text
    char* text = (argc == 3) ? argv[2] : argv[1]; // text is arg 2 if there is a 2nd argument, otherwise it is arg 1
    FILE* fp = fopen(text, "r"); // file pointer fp points to text, open it for reading
    if (fp == NULL) // if the file is null/0, then stop running program and return error
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n"); //print 'misspelled words' to console

    // prepare to spell-check 
    int index = 0, misspellings = 0, words = 0; // start counters for misspelllings
    char word[LENGTH+1]; // make an array called word with room for letters plus one 

    // spell-check each word in text
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) // int c is the character pointed to by file pointer in text, advance until end of file 
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0)) // if character is alphabetical, or it is an apostrophe
        {
            // append character to word
            word[index] = c; //write character to word array
            index++; //advance word array index

            // ignore alphabetical strings too long to be words
            if (index > LENGTH) // if index is greater than the length of the word, 
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(fp)) != EOF && isalpha(c)); // consume remainder of letters

                // prepare for new word 
                index = 0; // reset index to 0 for new word
            }
        }

        // ignore words with numbers (like MS Word can)
        else if (isdigit(c)) // ignore words with numbers
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(fp)) != EOF && isalnum(c));

            // prepare for new word
            index = 0;
        }

        // we must have found a whole word
        else if (index > 0)  // if there's a word
        {
            // terminate current word
            word[index] = '\0';  // end current word

            // update counter 
            words++; //update word counter to reflect new word

            // check word's spelling
            getrusage(RUSAGE_SELF, &before); // measure usage before checking spelling
            bool misspelled = !check(word); // check spelling of word (returns true or false)
            getrusage(RUSAGE_SELF, &after); // measure usage after checking spelling 

            // update benchmark
            time_check += calculate(&before, &after); // update calculation to include check time

            // print word if misspelled
            if (misspelled) // if a word is misspelled, print the word string and increase count of misspellings
            {
                printf("%s\n", word);
                misspellings++;
            }

            // prepare for next word
            index = 0;
        }
    }

    // check whether there was an error
    if (ferror(fp)) 
    {
        fclose(fp);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // close text
    fclose(fp);

    // determine dictionary's size
    getrusage(RUSAGE_SELF, &before); //get stats before checking dictionary size
    unsigned int n = size(); // set n to equal result of running size function
    getrusage(RUSAGE_SELF, &after); //get stats after checking dictionary size

    // calculate time to determine dictionary's size
    time_size = calculate(&before, &after);  //calculate time it takes to get dictionary's size

    // unload dictionary
    getrusage(RUSAGE_SELF, &before); // calculate stats before unloading dictionary
    bool unloaded = unload(); // return true or false for function unload dictionary
    getrusage(RUSAGE_SELF, &after); //calculate stats after loading dictionary

    // abort if dictionary not unloaded
    if (!unloaded) // if dictionary doesn't unload, quit program and return an error
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // calculate time to unload dictionary 
    time_unload = calculate(&before, &after); // calculate time it took to unload dictionary

    // report benchmarks 
    printf("\nWORDS MISSPELLED:     %d\n", misspellings); // print out all the stats measured
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n", 
     time_load + time_check + time_size + time_unload);

    // that's all folks
    return 0;
}

/**
 * Returns number of seconds between b and a.
 */
double calculate(const struct rusage* b, const struct rusage* a) //calculates run time
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
