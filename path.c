#include "main.h"
/**
 * getAbsolutePath - gets the absolute path of a command
 * @command: command to execute
 * Return: Absolute path of the command if found, otherwise NULL.
 */
char *getAbsolutePath(char *command)
{
	char *pathDirectory[MAX_ARGS + 2];
	int numDirectory = 0, i;
	char *token, *pathEnvVar;
	char tempCmd[BUFFER_SIZE];

	if (command[0] == '/')
	{
		return (_strdup(command));
	}
	pathDirectory[numDirectory++] = "/bin"; /* add /bin to search path */
	pathEnvVar = getenv("PATH");
	token = _strtok(pathEnvVar, ":");
	while (token != NULL)
	{
		pathDirectory[numDirectory++] = token;
		if (numDirectory >= MAX_ARGS + 1)
		{ /* increase size check accordingly */
			break;
		}
		token = _strtok(NULL, ":");
	}
	pathDirectory[numDirectory] = NULL;
	for (i = 0; i < numDirectory; i++)
	{
		int pathLen = _strlen(pathDirectory[i]);
		int cmdLen = _strlen(command);

		if (pathLen + cmdLen + 2 > BUFFER_SIZE)
		{ /* Check if the combined length exceeds buffer size */
			continue;
		}
		_strcpy(tempCmd, pathDirectory[i]);
		tempCmd[pathLen] = '/';
		_strcpy(tempCmd + pathLen + 1, command);
		if (access(tempCmd, X_OK) == 0)
		{
			return (_strdup(tempCmd));
		}
	}
	return (NULL);
}
