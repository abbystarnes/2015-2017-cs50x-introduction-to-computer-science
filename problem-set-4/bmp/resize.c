/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize multiplier infile outfile\n");
        return 1;
    }
    

    long n = strtol(argv[1], NULL, 10);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    
    //change size by n
    
    //old variables
    //DWORD bfSizeOld = bf.bfSize;
    LONG biWidthOld = bi.biWidth;
    //LONG biHeightOld = bi.biHeight;
    //DWORD biSizeImageOld = bi.biSizeImage;
    
    //new variables
    
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    // determine padding for scanlines
    int paddingOld =  (4 - (biWidthOld * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("%d\n", paddingOld);
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("%d\n", padding);
    bi.biSizeImage = bi.biWidth * abs(bi.biHeight) * sizeof(RGBTRIPLE) + padding * abs(bi.biHeight); /* ISSUE */
    bf.bfSize = bi.biSizeImage + bf.bfOffBits;
    // write outfile's header files
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //WRITING WIDTH HEIGHT TIMES
    // iterate over infile's scanlines
    //biHeightOld = abs(biHeightOld);
    int v = 1;
    //for (int b = 0; b < n; b++) { // write pixels for
        for (int i = 0; i < abs(bi.biHeight); i++)
        {
             // write pixels for as long as n is
                //WRITING WIDTH
                
                // iterate over pixels in scanline
                for (int j = 0; j < biWidthOld; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
                   
        
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    // write RGB triple to outfile
                    for (int a = 0; a < n; a++) {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                    
                    
                }   
                
                // skip over padding, if any
                
                fseek(inptr, paddingOld, SEEK_CUR);
                    
                for (int k = 0; k < padding; k++) //new padding amount
                {
                    fputc(0x00, outptr);
                }
                
                int moveBack = (biWidthOld * (sizeof(RGBTRIPLE)) + paddingOld);
                
                if (v % n != 0) {
                    fseek(inptr, -(moveBack), SEEK_CUR);
                };
                
                v++;
                
        
        }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
