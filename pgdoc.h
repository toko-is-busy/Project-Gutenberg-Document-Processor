/********************************************************************************************************* 
	This is to certify that this project is my own work, based on my personal efforts in studying 
	and applying the concepts learned. I have constructed the functions and their respective 
	algorithms and corresponding code by myself. The program was run, tested, and 
	debugged by my own efforts. I further certify that I have not copied in part or whole or 
	otherwise plagiarized the work of other students and/or persons.
                                                                <Yasmin Audrey T. Datario>, DLSU ID# <12172081> 
*********************************************************************************************************/

#define MAX_CHAR_LENGTH 10001
#define MAX_WORD_LENGTH 100
#define MAX_DETAILS 512
#define MAX_ENTRIES 2000

typedef char file[100];
typedef struct lines sentence;

struct bookContents
{
	char title[MAX_DETAILS];
	char author[MAX_DETAILS];
	char release[MAX_DETAILS];
	char language[MAX_DETAILS];
	char produce[MAX_DETAILS];
	char content[MAX_CHAR_LENGTH];
};

struct contentToProcess
{
	char content[MAX_CHAR_LENGTH];
};

typedef struct contentToProcess processData;
typedef struct bookContents contents;

struct wordsUsage
{
	char word[MAX_WORD_LENGTH];
	int	 count;
};

typedef struct wordsUsage wordUsed;

struct topWords
{
	wordUsed top[MAX_CHAR_LENGTH];
};

typedef struct topWords topCount;

struct gramStruct
{
	char word[MAX_WORD_LENGTH];
	int count;
};

typedef struct gramStruct gram;

struct topGrams
{
	gram top[MAX_CHAR_LENGTH];
};

typedef struct topGrams grams;

typedef struct pair{
    char key[MAX_CHAR_LENGTH];
    int value;
}pair;

typedef struct dictionary{
    int n;
    pair entries[MAX_ENTRIES];
}dictionary;
