#define _CRT_SECURE_NO_WARNINGS
#define N 7
#define byte unsigned char

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>



extern short int pincode;
extern short int CommandsNum;

typedef struct date
{
	short int day;
	short int month;
	short int year;
}Date;

typedef struct apartment
{
	short int code;
	char *address;
	int price;
	short int numRooms;
	struct date *date;
	struct date *entryDate;
	struct apartment *next;
	struct apartment *prev;
}Apartment;

typedef struct aptList
{
	struct apartment *head;
	struct apartment *tail;
}AptList;


typedef struct longTermList
{
	struct oldCommands *head;
	struct oldCommands *tail;
}LongTerm;

typedef struct oldCommands
{
	char *command;
	struct oldCommands *next;
	struct oldCommands *prev;
}OldCommands;

char *getCommand(int *size);

//Apt list
void makeEmptyAptList(AptList* lst);
void insertDataToAptList(AptList* lst, short int code, char *address, int price, short int numRooms, Date *date, Apartment *next, Apartment *prev,Date *entryDate);
void insertNodeToAptList(AptList* lst, Apartment * newTail);
Apartment* createNewApartment(short int code, char *address, int price, short int numRooms, Date *date, Apartment *next, Apartment *prev, Date *entryDate);
void freeAptList(AptList *lst);
void removeApt(Apartment *prev,AptList *res);
void printApt(Apartment* apt);


//StorageList
void makeEmptyStorageList(LongTerm* lst);
void insertDataToStorage(LongTerm* lst, char* command, OldCommands* next, OldCommands* prev);
void insertNodeToLongTerm(LongTerm* lst, OldCommands* newCommand);
LongTerm* createNewCommand(char* command, OldCommands* next, OldCommands* prev);
void insertNodeToHead(LongTerm* lst, OldCommands* newCommand);


//date
Date *createNewDate(short int day, short int month, short int year);
Date *getCurrDate();
short int getDay(short int days);
Date *getStartDate(short int days);

//command
void selectedCommand(char *str, AptList *res, char *short_term_history[N], LongTerm *storage);
void get_an_apt(char *str, AptList *res,char* sort);
void add_an_apt(char *str, AptList *res);
void buy_an_apt(char *str, AptList *res);
void delete_an_apt(char *str, AptList *res);

//get-an-apt
void maximumPrice(char *str, AptList *res,char* sort);
void maximumRooms(char *str, AptList *res, char* sort);
void minimunRooms(char *str, AptList *res, char* sort);
void getDate(char *str, AptList *res, char* sort);
void aptEnter(char *str, AptList *res, char* sort);

//storage
void addTermStorage(char** short_term_history, char* command,int size,LongTerm *list);

//file
void openFile(char *filename1, char *filename2, AptList *list, char** short_term_history, LongTerm *Commandlist);
void loadList(FILE* file1, AptList *list);
void loadStorage(FILE* file2, char** short_term_history, LongTerm *Commandlist);
void saveFile(char* filename1, char* filename2, AptList list, char** short_term_history, LongTerm Commandlist);
void saveBits(Apartment *curr, FILE* file);
Date* readBit(short int *numRooms, FILE* file);

//restore commands
void restored(char *str, AptList *res,char **short_term_history, LongTerm *storage);
void lastCommand(AptList *res, char **short_term_history, LongTerm *storage);
void numCommand(char *str, AptList *res, char **short_term_history, LongTerm *storage);
void short_history(AptList *res, char **short_term_history, LongTerm *storage);
void history(AptList *res, char **short_term_history, LongTerm *storage);
void str_str(char *str, AptList *res, char **short_term_history, LongTerm *storage);
char* findCommand(int num, AptList *res, char **short_term_history, LongTerm *storage);

//free
void freeApt(AptList *list);
void freeStorage( LongTerm *list);
void removeCommand(OldCommands *prev, LongTerm *list);


