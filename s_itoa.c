#include "main.h"
/**
 * s_itoa - converts int to a string
 * @num: integer to be converted
 * @str: string converted.
 * Return: on success, the str is returned.
 */
char *s_itoa(int num, char *str)
{
	int i = 0;
	int is_negative = 0;
	int j;

	/* Handle negative numbers*/
	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}

	/* Convert the number to string in reverse order*/
	do {
		str[i++] = num % 10 + '0';
		num /= 10;
	} while (num);

	/* Add the negative sign if necessary*/
	if (is_negative)
		str[i++] = '-';

	/* Reverse the string*/
	for (j = 0; j < i / 2; j++)
	{
		char temp = str[j];

		str[j] = str[i - j - 1];
		str[i - j - 1] = temp;
	}

	/* Null-terminate the string*/
	str[i] = '\0';

	return (str);
}
