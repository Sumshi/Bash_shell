#include "main.h"
/**
 * mySetEnv - sets the environment
 * @var: variable to set
 * @value: value to set
 * Return: Always 0.
 */
int mySetEnv(char *var, char *value)
{
	if (setenv(var, value, 1) != 0)
	{
		perror("setenv error");
		return (-1);
	}

	return (0);
}
/**
 * myUnsetEnv - unsets the environment
 * @var: environment variable
 * Return: Always 0.
 */
int myUnsetEnv(char *var)
{
	if (unsetenv(var) != 0)
	{
		perror("unsetenv error");
		return (-1);
	}

	return (0);
}
