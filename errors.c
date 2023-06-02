#include "main.h"

/**
 * ctrl_c - detect the CTRL+C signal and print another line with the prompt.
 * @x: idk.
 */
void ctrl_c(__attribute__((unused)) int x)
{
	signal(SIGINT, ctrl_c);
	write(1, "\n", 1);
	write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
}

/**
 * print_error - print specific errors to standard output.
 * @program_name: argv[0] of main.
 * @input: command that produces the error.
 * @error_num: error number - identifies the error type.
 */
void print_error(char *program_name, char *input, int error_num)
{
	char *str;

	if (error_num == 127) /* command not found */
	{
		write(STDOUT_FILENO, program_name, _strlen(program_name));
		write(STDOUT_FILENO, ": 1: ", 5);
		write(STDOUT_FILENO, input, _strlen(input));
		write(STDOUT_FILENO, ": not found\n", 12);
	}
	if (error_num == 2) /* syntax error*/
	{
		str = "sh: 1: Syntax error: \"";
		write(STDOUT_FILENO, str, _strlen(str));
		write(STDOUT_FILENO, ";", 1);
		str = "\" unexpected\n";
		write(STDOUT_FILENO, str, _strlen(str));
	}
	if (error_num == 3) /* malloc can't allocate memory */
	{
		write(STDOUT_FILENO, program_name, _strlen(program_name));
		write(STDOUT_FILENO, ": 1: ", 5);
		str = "internal error allocating memory\n";
		write(STDOUT_FILENO, str, _strlen(str));
	}
}
