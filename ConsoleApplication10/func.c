
#include "Header.h"



char *getCommand(int *size)
{
	char ch;
	char *res;
	int lSize = 0;
	int phSize = 1;
	printf("\nPlease enter your command\n");
	res = (char *)malloc((phSize + 1) * sizeof(char));
	ch = getchar();
	while (ch != '\n') /* new line is the end of the input */
	{
		if (lSize == phSize) /* there is NOT enough space */
		{
			phSize *= 2;
			res = (char*)realloc(res, (phSize + 1) * sizeof(char));   
		}
		res[lSize] = ch;
		lSize++;
		ch = getchar();
	}
	res[lSize] = '\0';
	lSize++;
	*size = lSize;
	res = (char*)realloc(res, (lSize) * sizeof(char));
	return res;

}

void addTermStorage(char** short_term_history, char* command,int size,LongTerm *List)
{
	CommandsNum++;
	int i = 0;
	char *temp;
	temp = (char*)malloc(sizeof(char)*size);
	strcpy(temp, command);
	temp[size] = '\0';
	while (short_term_history[i] != NULL&&i <= N)
		i++;
	if (i <= N)
		short_term_history[i] = temp;
	else
	{
		insertDataToStorage(List, short_term_history[0], NULL, NULL); 
		for (i = 0; i < N - 1; i++)
			short_term_history[i] = short_term_history[i + 1];
		short_term_history[N - 1] = temp;
	}


}
void selectedCommand(char *str, AptList *res, char *short_term_history[N], LongTerm *storage)
{
	switch (str[0])
	{
	case ('!'):restored(str, res, short_term_history, storage);
		break;
	case ('s'):restored(str, res, short_term_history, storage);
		break;
	case ('h'):restored(str, res, short_term_history, storage);
		break;
	}
	char *token;
	char *sort = strstr(str, "sr");
	token = strtok(str, " ");
	int size = strlen(token);
	switch (str[0])
	{
	case ('g'):get_an_apt(strtok(NULL, " "), res, sort);
		break;
	case ('a'):add_an_apt(strtok(NULL, "\""), res);
		break;
	case ('b'):buy_an_apt(strtok(NULL, "\n"), res);
		break;
	case ('d'):delete_an_apt(strtok(NULL, " "), res);
		break;

	}
	free(str);
}
void get_an_apt(char *str, AptList *res,char *sort)
{
	while (str != NULL)
	{
		if (strcmp(str, "-MaximumPrice") == 0)
		{
			maximumPrice(strtok(NULL, " "), res, sort);
		}
		else if (strcmp(str, "-MinimumNumRooms") == 0)
		{
			minimunRooms(strtok(NULL, " "), res, sort);
		}
		else if (strcmp(str, "-MaximumNumRooms") == 0)
		{
			maximumRooms(strtok(NULL, " "), res, sort);			
		}
		else if (strcmp(str, "-Date") == 0)
		{
			getDate(strtok(NULL, " "), res, sort);
		}
		else if (strcmp(str, "-Enter") == 0)
		{
			aptEnter(strtok(NULL, " "), res, sort);
		}
		str = strtok(NULL, " ");
	}


}
void add_an_apt(char *str, AptList *res)
{
	char *token, *address;
	char *command;
	int size;
	Date *date;
	pincode++;

	Apartment *curr = res->head;
	size = strlen(str);
	address = (char*)malloc((size + 1) * sizeof(char));
	strcpy(address, str);
	address[size] = '\0';

	token = strtok(NULL, " ");
	int price = atoi(token);
	token = strtok(NULL, " ");
	short int numRooms = atoi(token);
	token = strtok(NULL, " ");
	short int day = atoi(token);
	token = strtok(NULL, " ");
	short int month = atoi(token);
	token = strtok(NULL, " ");
	short int year = atoi(token);
	date = createNewDate(day, month, year);

	

	while (curr->next != NULL && curr->next->price <= price)
		curr = curr->next;
	insertDataToAptList(res, pincode, address, price, numRooms, date, curr->next, curr,NULL);
}
void buy_an_apt(char *str, AptList *res)
{
	short int code = atoi(str);
	Apartment *curr=res->head;
	while (curr->next!= NULL&&curr->next->code != code)
		curr=curr->next;
	if (curr->next != NULL&&curr->next->code == code)
	{
		if (pincode == curr->next->code)
		{
			pincode--;
		}
		removeApt(curr, res);
	}
	else
		printf("Apartment not found\n");

	
}

void delete_an_apt(char *str, AptList *res)
{

	Apartment *curr = res->head->next;
	Apartment *prev = res->head;
	str = strtok(NULL, " ");
	short int days = atoi(str);

	Date* startDate = getStartDate(days);

	while (curr != NULL)
	{
		if (curr->entryDate->year >= startDate->year)
		{
			if (curr->entryDate->year > startDate->year)
			{
				removeApt(prev, res);
				curr = prev;
			}
			else
			{
				if (startDate->month <= curr->entryDate->month)
				{
					if (startDate->day <= curr->entryDate->day)
					{
						removeApt(prev, res);
						curr = prev;
					}
				}
				else
				{
					removeApt(prev, res);
					curr = prev;
				}
			}
		}
		prev = curr;
		curr = curr->next;
	}
}



void aptEnter(char *str, AptList *res, char* sort)
{
	Apartment *curr = res->head->next;
	short int days = atoi(str);
	Date* startDate = getStartDate(days);
	printf("The apartments' entered in the last %d  days codes are:\n", days);
	days = getDay(days);
	int found = 0;
	if (sort != NULL)
	{
		curr = res->tail;
		while (curr != res->head)
		{
			if (curr->entryDate->year >= startDate->year)
			{
				if (curr->entryDate->year > startDate->year)
				{
					printf("%d\n", curr->code);
					found = 1;
				}
				else
				{
					if (startDate->month <= curr->entryDate->month)
					{
						if (startDate->day <= curr->entryDate->day)
						{
							printf("%d\n", curr->code);
							found = 1;
						}
					}
					else
					{
						printf("%d\n", curr->code);
						found = 1;
					}
				}
			}
			curr = curr->prev;
		}
	}
	else
	{
		while (curr != NULL)
		{
			if (curr->entryDate->year >= startDate->year)
			{
				if (curr->entryDate->year > startDate->year)
				{
					printf("%d\n", curr->code);
					found = 1;
				}
				else
				{
					if (startDate->month <= curr->entryDate->month)
					{
						if (startDate->day <= curr->entryDate->day)
						{
							printf("%d\n", curr->code);
							found = 1;
						}
					}
					else
					{
						printf("%d\n", curr->code);
						found = 1;
					}
				}
			}
			curr = curr->next;
		}
	}
	if (found == 0)
		printf("There aren't any apartments of that sort\n");
}
short int getDay(short int days)
{
	short int resDays;
	time_t seconds;
	seconds = time(NULL);
	resDays =(short int) (seconds / 86400) - days;
	return resDays;
}

Date *getStartDate(short int days)
{
	Date *res = getCurrDate();
	short int newDay;
	short int days_in_month[] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	while (days > 0)
	{
		res->day--;
		if (res->day == 0)
		{
			res->month--;
			if (res->month == 0)
			{
				res->month = 12;
				res->year--;
			}
			res->day += days_in_month[(res->month)];
		}
		days--;
	}
	return res;
}

//---------------------get-an-apt---------------------------------//
void maximumPrice(char *str, AptList *res, char *sort)
{
	Apartment *curr;
	int found = 0;
	int maxPrice = atoi(str);
	printf("The apartments under %d are:\n", maxPrice);

	if (sort != NULL)
	{
		curr = res->tail;
		while (curr != res->head)
		{
			if (curr->price < maxPrice)
			{
				printApt(curr);
				found = 1;
			}
			curr = curr->prev;
		}
	}
	else
	{
		curr = res->head->next;
		while (curr != NULL&&curr->price < maxPrice)
		{
			printApt(curr);
			curr = curr->next;
			found = 1;
		}
	}
	if (found == 0)
		printf("There are no apartments under %d price.\n", maxPrice);

}
void maximumRooms(char *str, AptList *res,char* sort)
{
	Apartment *curr;
	int minRoom = atoi(str);
	int found = 0;
	printf("The apartments with under %d rooms are:\n", minRoom);
	if (sort != NULL)
	{
		curr = res->tail;
		while (curr != res->head)
		{
			if (curr->numRooms <= minRoom)
			{
				printApt(curr);
				found = 1;
			}
			curr = curr->prev;
		}

	}
	else
	{
		curr = res->head->next;
		while (curr != NULL)
		{
			if (curr->numRooms <= minRoom)
			{
				printApt(curr);
				found = 1;
			}
			curr = curr->next;
		}
	}
	if (found == 0)
		printf("There are no apartments under %d rooms.\n", minRoom);
}
void minimunRooms(char *str, AptList *res,char *sort)
{
	int found = 0;
	Apartment *curr;
	int minRoom = atoi(str);
	printf("The apartments with at least %d rooms are:\n", minRoom);
	if (sort != NULL)
	{
		curr = res->tail;
		while (curr != res->head)
		{
			if (curr->numRooms >= minRoom)
			{
				printApt(curr);
				found = 1;
			}
			curr = curr->prev;
		}

	}
	else
	{
		curr = res->head->next;
		while (curr != NULL)
		{
			if (curr->numRooms >= minRoom)
			{
				printApt(curr);
				found = 1;
			}
			curr = curr->next;
		}
	}
	if (found == 0)
		printf("There are no apartments under %d rooms.\n", minRoom);
}
void getDate(char *str, AptList *res,char *sort)
{
	int flag = 0;
	Apartment *curr;
	char day[3], month[3], year[3];

	day[0] = str[0];
	day[1] = str[1];
	day[2] = '\0';

	month[0] = str[2];
	month[1] = str[3];
	month[2] = '\0';

	year[0] = str[6];
	year[1] = str[7];
	year[2] = '\0';

	if (sort != NULL)
	{
		curr = res->tail;
		while (curr != res->head)
		{
			if (curr->date->year <= atoi(year))
				if (curr->date->month < atoi(month))
				{
					printApt(curr);
					flag = 1;
				}
				else if (curr->date->month == atoi(month) && curr->date->day < atoi(day))
				{
					printApt(curr);
					flag = 1;
				}
			curr = curr->prev;
		}
	}
	else {
		curr = res->head->next;
		while (curr != NULL)
		{
			if (curr->date->year <= atoi(year))
				if (curr->date->month < atoi(month))
				{
					printApt(curr);
					flag = 1;
				}
				else if (curr->date->month == atoi(month) && curr->date->day < atoi(day))
				{
					printApt(curr);
					flag = 1;
				}
			curr = curr->next;
		}
	}
	if(flag == 0)
		printf("There are no apartments evacuating before %s / %s / %s", day, month, year);

}



