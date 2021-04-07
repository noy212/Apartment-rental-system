#include "Header.h"



void makeEmptyAptList(AptList* lst)
{
	Date *date;
	date = createNewDate(-1, -1, -1);
	lst->head = createNewApartment(-1, '\0', -1, -1, date, NULL, NULL);
	lst->tail = lst->head;
}
void insertDataToAptList(AptList* lst, int code, char *address, int price, short int numRooms, Date *date, Apartment *next, Apartment *prev)
{
	Apartment* newApt;

	newApt = createNewApartment(code, address, price, numRooms, date, next, prev);
	insertNodeToAptList(lst, newApt);
}
void insertNodeToAptList(AptList* lst, Apartment * newApt)
{

	if (lst->head->next == NULL)
	{
		lst->head->next = lst->tail = newApt;
		//		lst->tail->prev = lst->head = newApt;
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
Apartment* createNewApartment(int code, char *address, int price, short int numRooms, Date *date, Apartment *next, Apartment *prev)
{

	Apartment* res;

	res = (Apartment*)malloc(sizeof(Apartment));
	res->code = code;
	if (address == NULL)
	{
		res->address = (char*)malloc(1 * sizeof(char));
		res->address = "-1";
	}
	else
	{
		res->address = (char*)malloc(strlen(address) * sizeof(char));
		strcpy(res->address, address);
	}
	res->price = price;
	res->numRooms = numRooms;
	res->date = createNewDate(date->day, date->month, date->year);
	res->next = next;
	res->prev = prev;
	//תאריך יצירה
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

void removeApt(Apartment *prev)
{
	//לתקן טייל
	Apartment *toDelete = prev->next;
	prev->next = toDelete->next;
//	free(toDelete->address);
//	free(toDelete->date);
	free(toDelete);
}

void printApt(Apartment* apt)
{
	printf("\nCode: %d", apt->code);
	printf("\nAddress: %s", apt->address);
	printf("\nPrice: %d", apt->price);
	printf("\nDate: %d/%d/%d", apt->date->day, apt->date->month, apt->date->year);
	printf("\n");
}