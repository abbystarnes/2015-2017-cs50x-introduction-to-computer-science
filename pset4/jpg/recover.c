/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

//add libraries
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//define byte as an 8 bit integer
typedef uint8_t BYTE;

int main()
{   
    //string buffer = (string)malloc(512 * sizeof(BYTE));
    //char * buffer;
    //buffer = (char *)malloc(512 * sizeof(BYTE));
    BYTE buffer[512]; //define buffer for temp storage of jpeg blocks
    char title[8]; // define array for storing file names
    int fileNumber = 0;//how to write 000? //define a counter for increasing file numbers in names
    FILE* card = fopen("card.raw", "r"); //open card to read from, read only
    FILE * jpeg = 0; //create file pointer called jpeg whose content is null??
    
    if (card == NULL) //if the card is null, return an error
    {
        printf("File does not exist.\n");
        return 1;
    }
    
    //  (fread(&buffer, sizeof(buffer), 1, card) != NULL) {
     //loop through the card until reaching end of file
        
    while (fread(&buffer, sizeof(buffer), 1, card)) { //read into a chunk of memory one block in size, once, from the card file 
        

        //if start of a new jpeg
            //open a new file
            //close old file (if it exists)
            //advance file #
        
        //if no jpeg is found/no file is open
            // do nothing
        
        // if a jpeg has already been found
            // write to jpeg
        
        
        
        if ((buffer[0] == 255) && (buffer[1] == 216) && (buffer[2] == 255) && (buffer[3] >= 224 && buffer[3] <= 239)) { //if first 4 bytes of block are jpeg sequence
            //printf("found a jpeg!"); 
            //printf("%d", buffer[3]);
            
            if (jpeg != 0) {
                fclose(jpeg);
            }
            sprintf(title, "%03d.jpg", fileNumber); //print file title to array title ??
          //close file somehow
            //printf("%s", title);
            //jpeg = fopen (title, title); //set jpeg to equal opened file with title 'title'
            jpeg = fopen(title, "w");
            fileNumber ++; //increase file number (so next file will have next number name)
            //printf("%d", fileNumber); //print file number 
        } 
        
       
        
        if(jpeg == 0){ // if jpeg opened file worked, write buffer chunk to it
            
        }
        
        else {
            fwrite(buffer, sizeof(buffer), 1, jpeg);
        }
         
    
    }
    
//     do {
//   statement(s);
// } while( condition );
    
    
    

    fclose(card); //close card we read from
    fclose(jpeg); //close last open jpeg
    //free(buffer); // free buffer temp variable
                
            
   // printf("reached end\n"); //notify we made it to end of code     


    

}

// FILE *ifp, *ofp;
// char *mode = "r";
// char outputFilename[] = "out.list";

// ifp = fopen("in.list", mode);

// if (ifp == NULL) {
//   fprintf(stderr, "Can't open input file in.list!\n");
//   exit(1);
// }

// ofp = fopen(outputFilename, "w");

// if (ofp == NULL) {
//   fprintf(stderr, "Can't open output file %s!\n",
//           outputFilename);
//   exit(1);
// }




        
        
        
        
        
    
    
    
                //close old file (if one)
            // if (jpeg) {
            //     fclose(jpeg);
            //     printf("closed a jpeg file!");
            //     fileNumber ++;
            // }
            
            
            
            //fclose file#.jpeg
            //open new file
            //sprintf(title, "%d.jpg", 2);
            //FILE* img = fopen (title, "a");
        //} 
        
        
        
        //printf("%d.jpg", fileNumber);
        //file# = 0;
        //if start of new jpeg
        //if buffer = new jpeg signature {
        
        
            //printf("sizeof(buffer): %zu\n", sizeof(buffer));
    
    //open card file
    //fopen(card.raw, read);
    
    
    
    
    // loop until end of card
    //for (x=0, x<= card.raw.length, x++) {
    
    
    
            //if file is open
        //if file#.jpeg is open {
            //write to file
            //fwrite(buffer, 1, 1, FILE* );
               
    //}
    
    
        //fclose(file#.jpeg);
    //close any open files
    
        //free memory
        
        
         // read 512 bytes into buffer