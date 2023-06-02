#include "main.h"
/**
 * set_env - sets environment
 * @args: argument vector
 * Return: void
 */
void set_env(char **args)
{
	char *msg;

	if (args[1] == NULL || args[2] == NULL)
	{
		msg = "Usage: setenv VARIABLE VALUE\n";
		write(STDOUT_FILENO, msg, _strlen(msg));
	}
	if (mySetEnv(args[1], args[2]) != 0)
	{

	}
}
/**
 * unset_env - unsets environment
 * @args: argument vector
 * Return: void
 */
void unset_env(char **args)
{
	char *msg;

	if (args[1] == NULL)
	{
		msg = "Usage: unsetenv VARIABLE\n";
		write(STDOUT_FILENO, msg, _strlen(msg));
	}
	if (myUnsetEnv(args[1]) != 0)
	{

	}
}
