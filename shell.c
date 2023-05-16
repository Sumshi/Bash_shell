#include "main.h"
/**
 * main - program execution begins
 * Return: always 0 on success
 **/
int main(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t length;
	/*char command[100];*/
	int clear_requested = 0;

	setenv("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", 1);
	setenv("TERM", "xterm", 1);
	if (isatty(fileno(stdin)))
	{/*Checks if standard input is the terminal*/
		while (1)
		{
			if (clear_requested)
			{
				/*system("clear";Clear the terminal screen*/
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
			else
			{
				execute_command(buffer);
			}
			/*system("clear");*/
		}
	}
	else
	{/*Non-interactive mode = reads command from a file eg .sh scripts*/
		while ((length = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
		{
			buffer[length - 1] = '\0';
			execute_command(buffer);
		}
	}
	return 0;
}
