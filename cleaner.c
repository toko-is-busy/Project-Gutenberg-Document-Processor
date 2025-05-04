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

int Search_in_File();
void fileInput();

int removeChar(char * str, char charToRemmove){
    int i, j, removed = 0;
    int len = strlen(str);
    for(i=0; i<len; i++)
    {
        if(str[i] == charToRemmove)
        {
            for(j=i; j<len; j++)
            {
                str[j] = str[j+1];
            }
            len--;
            i--;
            removed++;
        }
    }
    
    return removed;
}

void lowerCase(processData data[], int charCount){
	int i;
	for(i = 0; i < charCount; i++)
	{
		if(data[0].content[i] >= 'A' && data[0].content[i] <= 'Z')
			data[0].content[i] = data[0].content[i] + 32;
	}
	
	//printf("\nTO LOWER: %s\n", data[0].content);
}

void removeSpecial(processData data[], int *charCount){
	int i, rep = 0, removed;
	while(rep < 5) 
	{
		for(i = 0; i < *charCount; i++)
		{
			if(!(data[0].content[i] >= 'A' && data[0].content[i] <= 'Z') && !(data[0].content[i] >= 'a' && data[0].content[i] <= 'z') && data[0].content[i] != ' ' && data[0].content[i] != '\n' && (data[0].content[i] < '0' || data[0].content[i] > '9'))
			{
				if(((data[0].content[i+1] >= 'A' && data[0].content[i+1] <= 'Z') || (data[0].content[i+1] >= 'a' && data[0].content[i+1] <= 'z') || (data[0].content[i+1] >= '0' && data[0].content[i+1] <= '9')) && ((data[0].content[i-1] >= 'A' && data[0].content[i-1] <= 'Z') || (data[0].content[i-1] >= 'a' && data[0].content[i-1] <= 'z') || (data[0].content[i-1] >= '0' && data[0].content[i-1] <= '9')))
					data[0].content[i] = ' ';
				else
					removed = removeChar(data[0].content,data[0].content[i]);
			}
		}
		rep++;
	}
	
	*charCount -= removed;
	//printf("\nREMOVE SPECIAL: %s\n", data[0].content);
}

void removeNumbers(processData data[], int *charCount){
	int i, rep = 0, removed;
	
	while(rep < 5) 
	{
		for(i = 0; i < *charCount; i++)
		{
			if((data[0].content[i] >= '0' && data[0].content[i] <= '9'))
				removed = removeChar(data[0].content,data[0].content[i]);
		}
		rep++;
	}
	
	*charCount -= removed;
	//printf("\nREMOVE NUMBER: %s\n", data[0].content);
}

void cleanWhitespace(processData data[], int *charCount){
	int i, j, len, removed = 0, rep =0;
	
	while(rep < 5) 
	{
		len = strlen(data[0].content);
		for(i=0; i<len; i++)
		{
		   if(data[0].content[0]==' ')
		   {
		      for(i=0; i<(len-1); i++)
		      	data[0].content[i] = data[0].content[i+1];
		      
			  data[0].content[i] = '\0';
		      len--;
		      i = -1;
		      removed++;
		   }
		   
		   if(data[0].content[i]==' ' && data[0].content[i+1]==' ')
		   {
		      for(j=i; j<(len-1); j++)
		         data[0].content[j] = data[0].content[j+1];
		      
		      data[0].content[j] = '\0';
		      len--;
		      i--;
		      removed++;
		   }
		   
		   if(data[0].content[i] == '\n')
		   		data[0].content[i] = ' ';
		}
		rep++;
	}
	
	*charCount -= removed;
	//printf("\nREMOVE WHITESPACE: %s\n", data[0].content);
}

void allPreProcessing(processData data[], int *charCount){	
	int rep = 0;
	
	while(rep < 5)
	{
		lowerCase(data,*charCount);
		removeSpecial(data,&*charCount);
		removeNumbers(data,&*charCount);
		cleanWhitespace(data,&*charCount);
		rep++;
	}
	
	//printf("\nALL PROCESS: %s\n", data[0].content);
}

void saveCleanedData(contents book[], int *charCount){
	file fileName;
	//allPreProcessing(data,&*charCount);
	
	printf("\nCLEANED: %s\n", book[0].content);
	
	printf("\nEnter filename for cleaned data: ");
	scanf("%s", fileName);
	strcat(fileName,".txt");
	
	FILE *pFile;
	pFile = fopen(fileName, "w");
	
	fprintf(pFile, "%s", book[0].title);
	fprintf(pFile, "%s", book[0].author);
	fprintf(pFile, "%s", book[0].release);
	fprintf(pFile, "%s", book[0].language);
	fprintf(pFile, "%s", book[0].produce);
	fprintf(pFile, "Content:\n%s", book[0].content);
	
	fclose(pFile);
	printf("\nCleaned data saved to %s!\n************************************************\n", fileName);
}

int dataCleaner()
{
	int charNum, charCount;
	char cChoice;
	contents book[1];
	file fileName;
	processData data[1];
	
	printf("\n************************************************\nDATA CLEANER\n");
	fileInput(book,&fileName,&charNum);
	
	Search_in_File(book,fileName,"Title",0);
	Search_in_File(book,fileName,"Author",0);
    Search_in_File(book,fileName,"Release",0);
    Search_in_File(book,fileName,"Language",0);
    Search_in_File(book,fileName,"Produced by",0);
	
	printf("\n************************************************\n");
	printf("%s", book[0].title);
	printf("%s", book[0].author);
    printf("%s", book[0].release);
    printf("%s", book[0].language);
    printf("%s", book[0].produce);
	printf("************************************************\n");
	
	charCount = Search_in_File(book,fileName,"*** START",charNum);
	strcpy(data[0].content, book[0].content);
	printf("%s\n\n", data[0].content); //Prints Raw Data
	
	do
	{
		printf("\nDATA CLEANER\n[1] To LowerCase\n[2] Remove Special Characters\n[3] Remove Numbers\n[4] Clean Whitespace\n[5] ALL Preprocessing tasks\n[6] Exit Data Cleaner\nUser Choice: ");
		scanf(" %c", &cChoice);
		
		switch(cChoice)
		{
			case '1': lowerCase(data,charCount); 
					printf("\nProcedure To LowerCase was successfully done!\n"); break;
			case '2': removeSpecial(data,&charCount);
					printf("\nProcedure to Remove Special Characters was successfully done!\n"); break;
			case '3': removeNumbers(data,&charCount);
					printf("\nProcedure to Remove Numbers was successfully done!\n"); break;
			case '4': cleanWhitespace(data,&charCount);
					printf("\nProcedure to Clear WhiteSpace was successfully done!\n"); break;
			case '5': allPreProcessing(data,&charCount); 
					printf("\nAll pre-processing tasks are successfully executed!\n"); break;
			case '6': strcpy(book[0].content, data[0].content);
					saveCleanedData(book,&charCount);
					 break;
			default: printf("\nInvalid choice!\n");
		}
	} while(cChoice != '6');
	
	return 0;
}
