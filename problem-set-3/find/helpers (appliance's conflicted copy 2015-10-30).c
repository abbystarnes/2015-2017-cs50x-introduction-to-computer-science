/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 


bool search(int value, int values[], int n){
        // implement a searching algorithm
        
            if(n <= 0) {
                return false;
            };    
            
            for(int i = 0; i < n; i++)
            {
               if(values[i] == value)
               {
                    return true;
               };
       
                
            };
            
            return false;

};

/**
 * Sorts array of n values.
 */
    void sort(int values[], int n)
    {
        // TODO: implement an O(n^2) sorting algorithm
        //
        //int array[100], n, c, d, position, swap;
        for (i = 0; i < n; i++)
        {
            position = i;
            
            for ( d = i + 1; d < n; d ++)
            {
                if ( array [position] > array [d] )
                    position = d;
            }
            
            if ( position != c )
            {
                int swap = array[c];
                int array[c] = array[position];
                int array[position] = swap;
            }    
            
        };    
        return;
    };


