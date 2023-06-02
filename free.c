#include "main.h"

/**
 * freedata - frees data
 * @data: the data structure
 *
 * Return: (Success) positive number
 *		(Fail) negative number
 */
int freedata(main_t *data)
{
	free(data->line);
	data->line = NULL;
	free(data->args);
	data->args = NULL;
	free(data->cmd);
	data->cmd = NULL;
	free(data->error_msg);
	data->error_msg = NULL;
	return (0);
}
/**
 * array_build- fill an array with elements
 * @a: the given array
 * @element: the given element
 * @len: the length of the array
 *
 * Return: pointer to filled array
 */
void *array_build(void *a, int element, unsigned int len)
{
	char *p = a;
	unsigned int i = 0;

	while (i < len)
	{
		*p = element;
		p++;
		i++;
	}
	return (a);
}
