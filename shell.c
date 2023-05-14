#include "main.h"
/**
 * main - program execution begins
 * Return: always 0 on success
 **/
int main(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t length;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);/*display prompt*/
		length = read(STDIN_FILENO, buffer, BUFFER_SIZE);

		if (length == 0)/*end of file reached*/
		{
			write(STDOUT_FILENO, "Exiting shell...\n", 17);
			break;
		}
		buffer[length - 1] = '\0';/*remove newline*/
		if (_strcmpr(buffer, "exit") == 0)
		{/*Check for exit command*/
			break;
		}

		execute_command(buffer);
	}
	return (0);
}
