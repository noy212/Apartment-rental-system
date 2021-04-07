#include "Header.h"

void restored(char *str, AptList *res, char **short_term_history, LongTerm *storage)
{
	switch (str[1])
	{
	case ('!'): lastCommand(res, short_term_history, storage);
		break;
	case ('h'): short_history(res, short_term_history, storage);
		break;
	case ('i'): history(res, short_term_history, storage);
		break;
	default:
	{
		if (strstr(str, "^") == NULL)
			numCommand(str, res, short_term_history, storage);
		else
			str_str(str, res, short_term_history, storage);
	}
	}
}

void lastCommand(AptList *res, char **short_term_history, LongTerm *storage)
{
	int i = N - 1;
	int len;
	char*temp;

	while (short_term_history[i] == NULL)
		i--;
	printf("%s\n", short_term_history[i]);

	len = strlen(short_term_history[i]);
	temp = (char*)malloc(sizeof(char)*(1 + len));
	temp[len] = '\0';
	strcpy(temp, short_term_history[i]);

	addTermStorage(short_term_history, short_term_history[i], len, storage);
	selectedCommand(temp, res, short_term_history, storage);
}



void numCommand(char *str, AptList *res, char **short_term_history, LongTerm *storage)
{
	char* command;
	int len;
	int num = atoi(str + 1);
	command = findCommand(num, res, short_term_history, storage);

	if (command != NULL)
	{
		len = strlen(command);
		addTermStorage(short_term_history, command, len, storage);
		selectedCommand(command, res, short_term_history, storage);
	}
	else
		printf("theres no %d command", num);

}

void short_history(AptList *res, char **short_term_history, LongTerm *storage)
{
	short int count=0;
	int i;
	OldCommands *curr = storage->head;

	if (CommandsNum > N)
		count = CommandsNum-N;
	for (i = 0; i < N; i++)
		if (short_term_history[i] != NULL)
		{
			printf("%d. %s\n", ++count , short_term_history[i]);
		}

}


void history(AptList *res, char **short_term_history, LongTerm *storage)
{
	short int count= 0;
	int i;
	OldCommands *curr = storage->head;

	if (CommandsNum > N)
		while (curr != NULL)
		{
			printf("%d. %s\n", ++count, curr->command);
			curr = curr->next;

		}

	for (i = 0; i < N; i++)
		if (short_term_history[i] != NULL)
		{
				printf("%d. %s\n",++count, short_term_history[i]);
		}

}



void str_str(char *str, AptList *res, char **short_term_history, LongTerm *storage)
{
	char* command;
	char* newcommand;
	char* strToRemove;
	char* strToInsert;
	char* commandEnd;
	char* s;
	char* e;
	int len;
	int lenRemove;
	char* temp;
	
	int num = atoi(strtok(str, "^")+1);

	command = findCommand(num, res, short_term_history, storage);

	len = strlen(command);
	strToRemove = strtok(NULL, "^");
	s = strstr(command, strToRemove);

	if (s == NULL)
		printf("theres no %s in the command\n", strToRemove);
	else
	{
		lenRemove = strlen(strToRemove);
		strToInsert = strtok(NULL, "\0");
		e =s+ lenRemove;
		commandEnd = strtok(e, "\0");
		len = len - lenRemove + strlen(strToInsert);

		*s = '\0';
		newcommand = (char*)malloc(sizeof(char)*(len + 1));
		strcpy(newcommand, command);
		newcommand[len] = '\0';

		strcat(newcommand, strToInsert);

		if (commandEnd != NULL)
		{
			newcommand[len] = ' ';
			newcommand[len - strlen(e)] = '\0';
			strcat(newcommand, e);
		}
		len = strlen(newcommand);
		temp = (char*)malloc(sizeof(char)*(1 + len));
		strcpy(temp, newcommand);
		temp[len] = '\0';

		addTermStorage(short_term_history, temp, len, storage);
		selectedCommand(newcommand, res, short_term_history, storage);
	}
}

char* findCommand(int num, AptList *res, char **short_term_history, LongTerm *storage)
{
	char* command;
	int len;
	OldCommands *curr = storage->head;
	int count = 0;
	if (num <= CommandsNum)
	{
		if (CommandsNum - N >= num)
		{
			while (++count < num)
			{
				curr = curr->next;
			}

			len = strlen(curr->command);
			command = (char*)malloc(sizeof(char)*(len + 1));
			strcpy(command, curr->command);
			command[len] = '\0';

			return command;
		}
		else
		{
			if (N < CommandsNum)
				count = CommandsNum-N;
			len = strlen(short_term_history[num - count -1]);
			command = (char*)malloc(sizeof(char)*(len + 1));
			strcpy(command, short_term_history[num - count -1]);
			command[len] = '\0';

			return command;
		}
	}
	else
		return NULL;
}