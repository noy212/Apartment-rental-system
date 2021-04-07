#include "Header.h"



void makeEmptyStorageList(LongTerm* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}
void insertDataToStorage(LongTerm* lst, char* command, OldCommands* next, OldCommands* prev)
{
	OldCommands* newCommand;

	newCommand = createNewCommand(command,next,prev);
	insertNodeToLongTerm(lst, newCommand);
}
void insertNodeToLongTerm(LongTerm* lst, OldCommands* newCommand)
{

	if (lst->head == NULL)
		lst->head = lst->tail = newCommand;
	else
	{
		newCommand->prev = lst->tail;
		lst->tail->next = newCommand;
		lst->tail = newCommand;

	}
}
LongTerm* createNewCommand(char* command, OldCommands* next, OldCommands* prev)
{
	OldCommands* res;

	res = (OldCommands*)malloc(sizeof(OldCommands));
	res->command = command;
	res->next = next;
	res->prev = prev;
	return res;
}
void insertNodeToHead(LongTerm* lst, OldCommands* newCommand)
{
	if (lst->head == NULL)
		lst->head = lst->tail = newCommand;
	else
	{
		newCommand->next = lst->head;
		lst->head->prev = newCommand;
		lst->head = newCommand;

	}
}

void freeStorage(LongTerm *list)
{

	OldCommands *curr = list->tail->prev;
	OldCommands *prevCurr;
	while (curr != NULL)
	{
		prevCurr = curr->prev;
		removeCommand(curr,list);
		curr = prevCurr;
	}

	free(list->head);
}

void removeCommand(OldCommands *prev, LongTerm *list)
{
	int i;
	OldCommands *toDelete = prev->next;
	prev->next = toDelete->next;
	list->tail = prev;
	free(toDelete);
}

