#include "main.h"
size_t _strcspn(const char *str1, const char *str2)
{
	const char *p1, *p2;
	size_t count = 0;

	for (p1 = str1; *p1 != '\0'; p1++)
	{
		for (p2 = str2; *p2 != '\0'; p2++)
		{
			if (*p1 == *p2)
				return count;
		}
		count++;
	}

	return count;
}
#include "main.h"
int _strncmp(const char *str1, const char *str2, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}

		if (str1[i] == '\0')
		{
			return 0;
		}
	}
	return 0;
}
