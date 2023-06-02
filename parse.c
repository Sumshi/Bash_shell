#include "main.h"
/**
 * parseInput - tokenizes the input
 * @input: input passed.
 * @args: arguments passes
 * Return: Always 0.
 */
void parseInput(char *input, char **args)
{
	int last_exit_status = 0;
	char *token;
	int i = 0;
	int j;
	char pid[10];
	char exit_status[10];

	token = _strtok(input, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = _strtok(NULL, " ");
	}
	args[i] = NULL;
	/* Replace $?, $$ and $PATH variables */
	for (j = 0; args[j] != NULL; j++)
	{
		if (_strcmpr(args[j], "$?") == 0)
		{
			int len = int_to_string(exit_status, last_exit_status);

			write_string(args[j], exit_status, len);
		}
		else if (_strcmpr(args[j], "$$") == 0)
		{
			int len = int_to_string(pid, getpid());

			write_string(args[j], pid, len);
		}
		else if (_strcmpr(args[j], "$PATH") == 0)
		{
			args[j] = _strdup(getenv("PATH"));
		}
	}
}

/**
 * int_to_string - converts an integer to a string
 * @str: destination buffer to store the string
 * @num: the integer to convert
 * Return: The length of the string
 */
int int_to_string(char *str, int num)
{
	int i = 0;
	int is_negative = 0;

	/*Handle negative numbers*/
	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}
	/*Convert each digit to a character in reverse order*/
	do {
		str[i++] = num % 10 + '0';
		num /= 10;
	} while (num > 0);
	/*Add the negative sign if necessary*/
	if (is_negative)
	{
		str[i++] = '-';
	}
	/*Reverse the string*/
	reverse_string(str, i);
	return (i);
}
