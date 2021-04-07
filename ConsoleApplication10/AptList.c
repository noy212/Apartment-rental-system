#include "Header.h"

void makeEmptyAptList(AptList* lst)
{
	Date *date;
	date = createNewDate(-1, -1, -1);
	lst->head = createNewApartment(-1, '\0', -1, -1, date, NULL, NULL,date);
	lst->tail = lst->head;
}

void insertDataToAptList(AptList* lst, short int code, char *address, int price, short int numRooms, Date *date, Apartment *next, Apartment *prev, Date *entryDate)
{
	Apartment* newApt;

	newApt = createNewApartment(code, address, price, numRooms, date, next, prev, entryDate);
	insertNodeToAptList(lst, newApt);
}
void insertNodeToAptList(AptList* lst, Apartment * newApt)
{

	if (lst->head->next == NULL)
	{
		lst->head->next = lst->tail = newApt;
	}
	else
	{
		newApt->prev->next = newApt;
		if (newApt->next != NULL)
			newApt->next->prev = newApt;
		else
			lst->tail = newApt;
	}
}
Apartment* createNewApartment(short int code, char *address, int price, short int numRooms, Date *date, Apartment *next, Apartment *prev,Date *entryDate)
{

	Apartment* res;
	int len;

	res = (Apartment*)malloc(sizeof(Apartment));
	res->code = code;
	if (address == NULL)
	{
		res->address = (char*)malloc(1 * sizeof(char));
		res->address = "-1";
	}
	else
	{
		len = strlen(address);
		res->address = (char*)malloc((len + 1) * sizeof(char));
			res->address[len] - '\0';
		strcpy(res->address, address);
	}
	res->price = price;
	res->numRooms = numRooms;
	res->date = createNewDate(date->day, date->month, date->year);
	if(code==-1)
		res->entryDate = createNewDate(-1, -1,-1);
	else
	{
		if (entryDate == NULL)
			res->entryDate = getCurrDate();
		else
			res->entryDate = entryDate;
	}
	
	res->next = next;
	res->prev = prev;
	return res;
}
void freeAptList(AptList *lst)
{
	Apartment* curr = lst->head, *saver;


	while (curr != NULL)
	{
		saver = curr->next;
		int i = 0;
		free(curr->address);
		free(curr->date);
		free(curr);
		curr = saver;
	}
}

Date *createNewDate(short int day, short int month, short int year)
{
	Date *date;
	date = (Date *)malloc(sizeof(Date));
	date->day = day;
	date->month = month;
	date->year = year;
	return date;
}

Date* getCurrDate()
{
	time_t currT;
	struct tm *currtime;
	Date *res;
	time(&currT);
	currtime = gmtime(&currT);

	short int day = (short int)currtime->tm_mday;
	short int month = (short int)(currtime->tm_mon + 1);
	short int year = (short int)((currtime->tm_year) % 100);
	res = createNewDate(day, month, year);
	return res;


}

void removeApt(Apartment *prev, AptList* res)
{
	int i;
	Apartment *toDelete = prev->next;
	prev->next = toDelete->next;
	
	if (toDelete->next == NULL)
		res->tail = prev;
	else
		toDelete->next->prev = toDelete->prev;
	free (toDelete->address);
	free(toDelete->date);
	free(toDelete->entryDate);
	free(toDelete);
}

void printApt(Apartment* apt)
{
	printf("\nCode: %d", apt->code);
	printf("\nAddress: %s", apt->address);
	printf("\nPrice: %d", apt->price);
	printf("\nNumber of Rooms: %d", apt->numRooms);
	printf("\nDate: %d/%d/%d", apt->date->day, apt->date->month, apt->date->year);
	printf("\nEntryDate: %d/%d/%d", apt->entryDate->day, apt->entryDate->month, apt->entryDate->year);
	printf("\n\n");
}



void freeApt(AptList *list)
{
	Apartment *curr = list->tail->prev;
	Apartment *prevCurr;
	while (curr!= NULL)
	{
		prevCurr = curr->prev;
		removeApt(curr, list);
		curr = prevCurr;
	}

	free (curr);
	free(list->head);
}