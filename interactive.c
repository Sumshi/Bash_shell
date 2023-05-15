/*#include "main.h"
int main(int argc, char *argv[])
{
	char buffer[BUFFER_SIZE];
	ssize_t length;

	if (argc > 1)
	{
		Read commands from the specified file
		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Failed to open file");
			exit(EXIT_FAILURE);
		}
		while (fgets(buffer, BUFFER_SIZE, file))
		{
			buffer[_strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
			execute_command(buffer);
		}

		fclose(file);
	}
	else
	{
		Read commands from standard input
		if (isatty(fileno(stdin)))
		{
			Interactive mode
			while (1)
			{
				write(STDOUT_FILENO, "$ ", 2);
				length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
				if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
				{
					perror("Exiting shell...\n");
					break;
				}

				buffer[_strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
				if (_strcmpr(buffer, "exit") == 0)
				{
					break;
				}

				execute_command(buffer);
			}
		}
		else
		{
			Non-interactive mode
			while (fgets(buffer, BUFFER_SIZE, stdin))
			{
				buffer[_strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
				execute_command(buffer);
			}
		}
	}

	return 0;
}
}*/
