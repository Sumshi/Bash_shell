#include "main.h"
/**
 * exitShell - exits shell
 * @exitStatus: value
 * Return: always 0
 **/
void exitShell(int exitStatus)
{
	exit(exitStatus);
}
/**
 * isComment - checks for comments
 * @line: value
 * Return: line
 **/
int isComment(const char *line)
{
	return (line[0] == '#');
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
