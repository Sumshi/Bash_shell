#include "main.h"
/**
 * main - program execution begins
 * Return: always 0 on success
 **/
int main(void) {
	char buffer[BUFFER_SIZE];
	ssize_t length;

	if (isatty(fileno(stdin))) {  // Checks if standard input is the terminal
		while (1) {
			write(STDOUT_FILENO, "$ ", 2);
			length = read(STDIN_FILENO, buffer, BUFFER_SIZE);

			if (length == 0) {
				write(STDOUT_FILENO, "Exiting shell...\n", 17);
				break;
			}

			buffer[length - 1] = '\0';
			if (_strcmpr(buffer, "exit") == 0) {
				break;
			}
			else if (_strncmp(buffer, "cd", 2) == 0)
			{
				execute_cd(buffer);
			}
			else
			{
				execute_command(buffer);
			}
		}
	} else {  // Non-interactive mode
		while ((length = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
			buffer[length - 1] = '\0';
			execute_command(buffer);
		}
	}

	return 0;
}
