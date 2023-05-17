#include "main.h"
void displayAliases()
{
	char command[100];
	const char* shell = getenv("SHELL");
	if (shell != NULL)
	{
		strcpy(command, shell);
		strcat(command, " -ic 'alias'");
		system(command);
	}
}
