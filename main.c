/********************************************************************************************************* 
	This is to certify that this project is my own work, based on my personal efforts in studying 
	and applying the concepts learned. I have constructed the functions and their respective 
	algorithms and corresponding code by myself. The program was run, tested, and 
	debugged by my own efforts. I further certify that I have not copied in part or whole or 
	otherwise plagiarized the work of other students and/or persons.
                                                                <your full name>, DLSU ID# <number> 
*********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int dataCleaner();
int dataAnalyzer();

int main()
{
	char cChoice;

	do
	{
		printf("\nMAIN VIEW\n[1] Data Cleaner\n[2] Data Analyzer\n[3] Exit Program\nUser Choice: ");
		scanf(" %c", &cChoice);
		
		switch(cChoice)
		{
			case '1': dataCleaner(); break;
			case '2': dataAnalyzer(); break;
			case '3': break;
			default: printf("\nInvalid choice!\n");
		}
	} while (cChoice != '3');
	
	return 0;
}
