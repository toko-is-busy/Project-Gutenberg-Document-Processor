/********************************************************************************************************* 
	This is to certify that this project is my own work, based on my personal efforts in studying 
	and applying the concepts learned. I have constructed the functions and their respective 
	algorithms and corresponding code by myself. The program was run, tested, and 
	debugged by my own efforts. I further certify that I have not copied in part or whole or 
	otherwise plagiarized the work of other students and/or persons.
                                                                <your full name>, DLSU ID# <number> 
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pgdoc.h"

int Search_in_File(contents book[], char *fname, char *str, int charNum){
    FILE *fp;
    file tempFile;
    int i, x, find_result = 0;
    char temp[512];
    
    for(x=0;x<512;x++)
    {
        temp[x] = '\0';
    }
    
    strcpy(tempFile,fname);
    strcat(tempFile,".txt");
    
    fp = fopen(tempFile, "r");
    

    while(fgets(temp, 512, fp) != NULL) {
        
        if((strstr(temp, str)) != NULL) {
            if(strcmp("Title", str) == 0)
                strcpy(book[0].title,temp);
            else if(strcmp("Author", str) == 0)
                strcpy(book[0].author,temp);
            else if(strcmp("Release", str) == 0)
                strcpy(book[0].release,temp);
            else if(strcmp("Language", str) == 0)
                strcpy(book[0].language,temp);
            else if(strcmp("Produced by", str) == 0)
                strcpy(book[0].produce,temp);
            else if(strcmp("*** START", str) == 0)
            {
                i = 0;
                while(charNum > 0 && !feof(fp))
                {
                    
                    book[0].content[i] = fgetc(fp);
                    //printf("[%d] %c\n", i, book[0].content[i]);
                    charNum--;
                    i++;
                }
                book[0].content[i] = '\0';
            }
            else if(strcmp("Content", str) == 0)
            {
                i = 0;
                while(charNum > 0 && !feof(fp))
                {
                    
                    book[0].content[i] = fgetc(fp);
                    //printf("[%d] %c\n", i, book[0].content[i]);
                    charNum--;
                    i++;
                }
                
                book[0].content[i] = '\0';
            }
            find_result++;
        }
    }
    
    if(find_result == 0) {
        printf("\nSorry, couldn't find %s.\n", str);
    }
    
    fclose(fp);
    return (i);
}

void fileInput(contents book[], file *fileName, int *charNum){
    file tempFile;
    FILE *pFile;
    
    printf("\nEnter File Location: ");
    scanf("%s", *fileName);
    
    strcpy(tempFile,(*fileName));
    strcat(tempFile,".txt");

    pFile = fopen(tempFile, "r");
    
    if (pFile == NULL)
    {
        while (pFile == NULL)
        {
            printf("File does not exist!\nPlease enter file location: ");
            scanf("%s", *fileName);
            
            strcpy(tempFile,(*fileName));
            strcat(tempFile,".txt");
            
            pFile = fopen(tempFile, "r");
        }
    }
    
    if(pFile != NULL)
    {
        printf("Enter max # of content char to process: ");
        scanf("%d", &*charNum);
    }
    
    fclose(pFile);
}
