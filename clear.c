#include "main.h"
/**
 * clear - cleans the screen
 * Return: Always 0.
 */
int clear(void)
{
	/*Clear the terminal screen using ANSI escape codes*/
	write(STDOUT_FILENO, "\033[2J", 4);
	write(STDOUT_FILENO, "\033[H", 3);
	return (0);
}
