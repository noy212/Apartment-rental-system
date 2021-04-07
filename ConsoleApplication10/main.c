#include "Header.h"
short int pincode = 0;
short int CommandsNum = 0;
void main(int argc,char**argv)
{
	int i;
	char *short_term_history[N];
	char *command;
	int size;

	AptList res;
	LongTerm storage;

	makeEmptyAptList(&res);
	makeEmptyStorageList(&storage);

	for (i = 0;i < N;i++) //in case there is no file
		(short_term_history)[i] = NULL;

	openFile( argv[1],  argv[2], &res,  short_term_history, &storage);

	command = getCommand(&size);

	while (command[0] != 'e')
	{
		if (command[0] != '!'&&command[0] != 'h'&&command[0] != 's')
			addTermStorage(short_term_history, command, size, &storage);
		selectedCommand(command, &res, short_term_history, &storage);
		command = getCommand(&size);
	}

	saveFile(argv[1], argv[2], res, short_term_history, storage);
	freeApt(&res);
	freeStorage(&storage);
}