#include "main.h"
/**
 * printEnv - prints environment
 * Return: Always 0.
 */
void printEnv(void)
{
	char **env;
	size_t len;

	for (env = environ; *env != NULL; env++)
	{
		len = _strlen(*env);
		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
	}
}
