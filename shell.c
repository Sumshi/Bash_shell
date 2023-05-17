#include "main.h"
/**
 * main - program execution begins
 * Return: always 0 on success
 **/
int main(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t length;
	int clear_requested = 0;
	bool pipe = false;
	setenv("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", 1);
	setenv("TERM", "xterm", 1);
	/*if (isatty(STDIN_FILENO) == 1)*/
	/*Checks if standard input is the terminal*/
	while (1 && !pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			pipe = true;
			if (clear_requested)
			{
				clear();
				clear_requested = 0;
			}
			write(STDOUT_FILENO, "$ ", 2);
			length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (length == 0)
			{
				write(STDOUT_FILENO, "Exiting shell...\n", 17);
				break;
			}
			buffer[length - 1] = '\0';
			if (_strcmpr(buffer, "exit") == 0)
			{
				break;
			}
			else if (_strncmp(buffer, "cd", 2) == 0)
			{
				execute_cd(buffer);/*executes cd command*/
			}
			else if (_strncmp(buffer, "env", 3) == 0)
			{
				print_environment();/*prints current environment*/
			}
			else if (_strcmpr(buffer, "clear") == 0)
			{
				clear_requested = 1;/*executes clear()*/
			}
			else if (strcmp(buffer, "alias") == 0)
			{
				displayAliases();
			}
			else
			{
				execute_command(buffer);
			}
	}
	return 0;
}
