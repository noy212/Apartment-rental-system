
#include "Header.h"

void openFile(char *filename1, char *filename2, AptList *list, char** short_term_history, LongTerm *Commandlist)
{
	FILE *file1, *file2;
	file1 = fopen(filename1, "rb");
	file2 = fopen(filename2, "rt");
	if (file1 == NULL &&file2 == NULL)
		return;

		loadList(file1, list);
		loadStorage(file2, short_term_history, Commandlist);
		fclose(file1);
		fclose(file2);
}

void loadStorage(FILE* file2, char** short_term_history, LongTerm *Commandlist)
{
	OldCommands *curr = Commandlist->tail;
	int i =N-1;
	int len;
	char *command;

	if (CommandsNum > N)
	{
		while (fscanf(file2, "%d", &len) != EOF && i >= 0)
		{
			short_term_history[i] = (char*)malloc(sizeof(char)*(len + 1));
			fgetc(file2);
			fgets(short_term_history[i], len + 1, file2);

			short_term_history[i][len] = '\0';
			fgetc(file2);
			i--;
		}

		while (fscanf(file2, "%d ", &len) != EOF)
		{
			command = (char *)malloc(sizeof(char)*(len + 1));

			fgets(command, len + 1, file2);
			command[len] = '\0';
			fgetc(file2);

			curr = createNewCommand(command, NULL, NULL);
			insertNodeToHead(Commandlist, curr);
		}
	}
	else
	{
		while (fscanf(file2, "%d", &len) != EOF && i >= 0)
		{
			short_term_history[i-(N-CommandsNum)] = (char*)malloc(sizeof(char)*(len + 1));
			fgetc(file2);
			fgets(short_term_history[i - (N - CommandsNum)], len + 1, file2);

			short_term_history[i - (N - CommandsNum)][len] = '\0';
			fgetc(file2);
			i--;

		}
	}
}


void loadList(FILE* file1, AptList *list)
{
	
	short int code;
	short int len;
	char *address;
	int price;
	short int numRooms;

	
	Date* date;
	Date* entryDate;
	short int enteryDay;
	short int enteryMonth;
	short int enteryYear;
	Apartment *curr=list->head;



	int n;

	fread(&pincode, sizeof(short int), 1, file1);
	fread(&CommandsNum, sizeof(short int), 1, file1);

	address = (char*)malloc(sizeof(char) * 1);
	while (n=fread(&code, sizeof(short int), 1, file1)>0)
	{
		fread(&len, sizeof(short int), 1, file1);
		address = (char*)realloc(address,(sizeof(char)*(len+1)));
		fread(address, sizeof(char), len, file1);
		address[len] = '\0';
		fread(&price, sizeof(int), 1, file1);

		date=readBit(&numRooms, file1);

		fread(&enteryDay, sizeof(short int), 1, file1);
		fread(&enteryMonth, sizeof(short int), 1, file1);
		fread(&enteryYear, sizeof(short int), 1, file1);


		entryDate = createNewDate(enteryDay, enteryMonth, enteryYear);
		insertDataToAptList(list, code, address, price, numRooms, date, NULL, curr, entryDate);

		curr = curr->next;

	}
}

Date* readBit(short int *numRooms,FILE* file)
{
	byte day;
	byte day2;
	byte month;
	byte year;
	byte year2;
	byte mask = 0;
	byte data[3] = { 0 };
	byte rooms;
	Date *date;
	fread(data, sizeof(byte), 3, file);

	rooms=  mask | data[0] >> 4;
	*numRooms = (short int)rooms;
	day = mask | data[0] << 4;
	day = day >>3;
	day2 = mask | data[1] >> 7;
	day = day | day2;
	month = mask | data[1] << 1;
	month = month >> 4;
	year = mask | data[1] << 5;
	year = year >> 1;
	year2 = mask | data[2] >> 4;
	year = year | year2;
	return date = createNewDate((short int)day,(short int)month,(short int)year);

}


void saveBits(Apartment *curr,FILE* file) 
{
	byte data[3] = { 0 };

	byte rooms = curr->numRooms << 4;
	byte day1 = curr->date->day >> 1;
	byte day2 = curr->date->day << 7;
	byte month = curr->date->month << 3;
	byte year1 = curr->date->year >> 4;
	byte year2 = curr->date->year << 4;
	data[0] = data[0] | rooms;
	data[0] = data[0] | day1;
	data[1] = data[1] | day2;
	data[1] = data[1] | month;
	data[1] = data[1] | year1;
	data[2] = data[2] | year2;
	fwrite(data, sizeof(byte), 3, file);
}

void saveFile(char* filename1, char* filename2, AptList list, char** short_term_history, LongTerm Commandlist)
{
	Apartment *curr = list.head->next;
	OldCommands *curr2 = Commandlist.tail;
	FILE* file;
	short int length;
	int i;




	//binary
	file = fopen(filename1, "wb");
	assert(file != NULL);

	fwrite(&pincode, sizeof(short int), 1, file);
	fwrite(&CommandsNum, sizeof(short int), 1, file);

	while (curr != NULL)
	{
		
		length = strlen(curr->address);
		fwrite(&(curr->code), sizeof(short int), 1, file);
		fwrite(&length, sizeof(short int), 1, file);
		fwrite(curr->address, sizeof(char), length, file);
		fwrite(&(curr->price), sizeof(int), 1, file);
		saveBits(curr,file);
		fwrite(&(curr->entryDate->day), sizeof(short int), 1, file);
		fwrite(&(curr->entryDate->month), sizeof(short int), 1, file);
		fwrite(&(curr->entryDate->year), sizeof(short int), 1, file);
		curr = curr->next;
	}
	fclose(file);

	//text
	file = fopen(filename2, "wt");
	assert(file != NULL);
	for (i = N-1;i >=0;i--)
	{
		if (short_term_history[i] != NULL)
		{
			fprintf(file, "%d ", strlen(short_term_history[i]));
			fprintf(file, "%s\n", short_term_history[i]);
		}
	}
	while (curr2 != NULL)
	{
		fprintf(file, "%d ", strlen(curr2->command));
		fprintf(file, "%s\n", curr2->command);
		curr2 = curr2->prev;
	}
	fclose(file);
}