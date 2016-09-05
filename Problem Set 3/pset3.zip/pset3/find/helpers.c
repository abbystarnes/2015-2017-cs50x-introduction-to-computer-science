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
        int first = 0;
        int last = n - 1;
        int middle = (first+last)/2;
        
        while (first <= last) 
        {
            if (values[middle] < value)
            {
                first = middle + 1;
            }
            else if (values[middle] == value) 
            {
                return true;
            }
            else
            {
                last = middle -1;
            }
            middle = (first + last)/2;
        }
        if (first > last)
        {
            return false;
        } 
        return false;   
            
        
       /* while length of list > 0
            look at middle of list
            if number found, return true
            else if number higher, search left
            else if number lower, search right
          return false
        
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
            
            return false; */

};

/**
 * Sorts array of n values.
 */
    void sort(int values[], int n)
    {
        // TODO: implement an O(n^2) sorting algorithm
		//selection sort
        int swapped = true;
		
		while (swapped == true)
		{
		    swapped = false;
		    for (int i = 0; i < n; i++)
		    {
		        
		        int j = i + 1;
		        
		        if (values[j] < values[i])
		        {
		            int temp;
		            temp = values[j];
		            values[j] = values[i];
		            values[i] = temp;
		            swapped = true;
		        }      
		    };
		}
        return;
        
    };


