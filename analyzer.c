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

char* substring(char *destination, const char *source, int beg, int n)
{
    // extracts `n` characters from the source string starting from `beg` index
    // and copy them into the destination string
    while (n > 0)
    {
        *destination = *(source + beg);
 
        destination++;
        source++;
        n--;
    }
 
    // null terminate destination string
    *destination = '\0';
 
    // return the destination string
    return destination;
}

int loadStrings(file fileName, char *words[], int charNum)
{
	file tempFile;
	char temp[512], line[MAX_CHAR_LENGTH];
	
	strcpy(tempFile, fileName);
	strcat(tempFile, ".txt");

	FILE *my;
	my = fopen(tempFile,"r");
	
	fgets(temp, 512, my);
	fgets(temp, 512, my);
	fgets(temp, 512, my);
	fgets(temp, 512, my);
	fgets(temp, 512, my);
	fgets(temp, 512, my);
	fgets(line, charNum+1, my);
	
	words[MAX_ENTRIES] = "\0";
	int i;
	int j = 0;
	int count = 0;
	char temp2[MAX_WORD_LENGTH];
	for(i=0; i<strlen(line); i++){
		if(line[i] == ' '){
			substring(temp2, line, j, i-j);
			j = i+1;
			//printf("%s\n", temp2);
			words[count] = (char *)malloc((strlen(temp2)+1)*sizeof(char));
			strcpy(words[count], temp2);
			count++;
		}
	}

	//strcpy(words[0], line);
	//printf("%d: %s\n",strlen(line), words[0]);
	
	fclose(my);
	printf("%d\n", count);
	for(i=0; i<count; i++){
		//printf("%s\n", words[i]);
	}
	return count;
}

int countOccurrences(char *str, char *toSearch)
{
    int i, j, found, count;
    int stringLen, searchLen;

    stringLen = strlen(str);      // length of string
    searchLen = strlen(toSearch); // length of word to be searched

    count = 0;

    for(i=0; i <= stringLen-searchLen; i++)
    {
        /* Match word with string */
        found = 1;
        for(j=0; j<searchLen; j++)
            if(str[i + j] != toSearch[j])
                found = 0;

        if(found == 1)
        	if(str[i + j - searchLen - 1] == ' ' && (str[i + j] == ' ' || i + j == stringLen))
            	count++;
    }

    return count;
}

void sortTop(topCount top[], int words)
{
	int x, y, nTemp;
	char temp[MAX_WORD_LENGTH];
	
	  for(x = 0; x < words - 1; x++)
	  {       
        for(y = 0; y < words - x - 1; y++)
		{          
            if(top[0].top[y].count > top[0].top[y + 1].count)
			{               
                nTemp = top[0].top[y].count;
                strcpy(temp, top[0].top[y].word);
                
                top[0].top[y].count = top[0].top[y + 1].count;
                strcpy(top[0].top[y].word, top[0].top[y + 1].word);

                top[0].top[y + 1].count = nTemp;
                strcpy(top[0].top[y + 1].word, temp);

            }
        }
	}
}

int deleteRepetition(topCount top[], int *j)
{
	int i, x, y = 1, nRun = 5;
	int *counts;
	counts = (int *)malloc(sizeof(int)*(*j));
	char words[MAX_ENTRIES] = "\0";
	
	for(i = 0; i <= *j; i++)
	{
		words[i] = (char *)malloc(sizeof(char)*(strlen(top[0].top[i].word)+1));
		strcpy(words[i], top[0].top[i].word);
		counts[i] = top[0].top[i].count;
	}
	
	while(nRun > 0)
	{
		for(i = 0 ; i <= *j ; i++)
		{
			for(y = i+1; y <= *j; y++)
	        {
	        	if(i == *j-1)
	        	{
	        		y = i;	
				}
				
	            if(strcmp(words[i],top[0].top[y].word) == 0)
	            {	
	                for(x = y; x <= *j; x++)
	                {
	                	if(x+1 != *j)
	                	{
	                		strcpy(top[0].top[x].word,top[0].top[x+1].word);
		                    top[0].top[x].count = top[0].top[x+1].count;
		                    
		                    strcpy(words[x],words[x+1]);
		                    counts[x] = counts[x+1];	
						}
	                }
	                (*j)--;
	            }
	        }
		}
		nRun--;
	}
	
	return *j;
	
}

int wordCount(processData data[], topCount top[]){
	int i, j, x, y, count;
	
	j = 0;
	x = 0;
    for(i = 0; i <= (strlen(data[0].content)); i++)
    {
        if(data[0].content[i]==' '||data[0].content[i]=='\0')
        {
            top[0].top[j].word[x]='\0';
            count = countOccurrences(data[0].content,top[0].top[j].word);
            top[0].top[j].count = count;
			
            j++;  //for next word
            x=0;    //for next word, init index to 0
        }
        else
        {
            top[0].top[j].word[x]=data[0].content[i];
            x++;
        }
    }
	
    sortTop(top,j);
	j = deleteRepetition(top,&j);
	printf("\nTOP 10 WORD COUNT:\n");
	i = 1;
	for(y=j;y>=j-10;y--)
	{
		printf("\t%-15s : %-2d\n", top[0].top[y].word, top[0].top[y].count);
		i++;
		
	}

	return j;
}

void ngram(dictionary *dict, char *string[], int length, int n){
    char temp_key[MAX_WORD_LENGTH];
    int i, j, k, found;
    printf("TEST");
	printf("%d", dict->n);
    dict->n = 0;
	printf("Here");
    char space_bar[] = " ";
    for(i=0; i<length-(n-1); i++){
        for(j=0; j<n; j++){
            if(j == 0){
                strcpy(temp_key, string[i+j]);
            }else{
                strcat(temp_key, space_bar);
                strcat(temp_key, string[i+j]);
            }
        }
        if(dict->n > 0){
            found = 0;
            for(k=0; k<dict->n; k++){
                if(strcmp(dict->entries[k].key, temp_key) == 0){
                    dict->entries[k].value++;
                    found = 1;
                }
            }
            if(!found){
                strcpy(dict->entries[dict->n].key, temp_key);
                dict->entries[dict->n].value = 1;
                dict->n++;
            }
        }else{
            strcpy(dict->entries[0].key, temp_key);
            dict->entries[0].value = 1;
            dict->n++;
        }
        printf("TEST");
        printf("%s\n", string[i]);
    }
}

int ngramCount()
{
	int n;
	
	do
	{
        n = 1;
        printf("\nEnter a value on n (1-4): ");
        scanf("%d", &n);
        
        if(n < 1 || n > 4)
            printf("\nInvalid! Choose from 1-4 only!\n");
    }while(n < 1 || n > 4);
    
    return n;
}

void saveFile(topCount top[], dictionary dict[], file filename, int nWords, int type){
	int i;
	file tempFile;
	
	strcpy(tempFile,filename);
	
	if(type == 1)
		strcat(tempFile,"_wcount.txt");
	else
		strcat(tempFile,"_ngram.txt");
	
	FILE *pFile;
	pFile = fopen(tempFile, "w");
	
	if(type == 1)
	{
		for(i = nWords; i >= 0; i--)
			fprintf(pFile, "%-15s:%d\n", top[0].top[i].word,top[0].top[i].count);
	}
	else
	{
		for(i = nWords; i >= 0; i--)
			fprintf(pFile, "%-20s:%d\n", dict->entries[i].key, dict->entries[i].value);
	}
	
	
	fclose(pFile);
	
	printf("\nWord Count saved to %s!\n************************************************\n", tempFile);
}

int dataAnalyzer()
{
	int n, charNum, nWords;
	int word_count;
	char cChoice, *words[MAX_CHAR_LENGTH];
	contents book[1];
	file fileName;
	processData data[1];
	topCount top[1];
	dictionary dict;
	
	
	printf("\n************************************************\nDATA ANALYZER\n");
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
	
	Search_in_File(book,fileName,"Content",charNum);
	strcpy(data[0].content, book[0].content);
	printf("\n%s\n", data[0].content); //Prints Raw Data
	
	
	do
	{
		printf("\nDATA ANALYZER\n[1] Word Count\n[2] N-gram Count\n[3] Exit Data Analyzer\nUser Choice: ");
		scanf(" %c", &cChoice);
		
		switch(cChoice)
		{
			case '1': nWords = wordCount(data,top);
					saveFile(top,&dict,fileName,nWords,1); break;
			case '2': word_count = loadStrings(fileName,words,charNum); n = ngramCount();
					ngram(&dict,words,word_count,n); saveFile(top,&dict,fileName,nWords,2); break;
			case '3': break;
			default: printf("\nInvalid choice!\n");
		}
	} while(cChoice != '3');
	
	return 0;
}
