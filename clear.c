#include "main.h"
int clear()
{
	// Clear the terminal screen using ANSI escape codes
	write(STDOUT_FILENO, "\033[2J", 4);
	write(STDOUT_FILENO, "\033[H", 3);
	return 0;
}
