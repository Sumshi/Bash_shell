#include "main.h"
/**
 * my_realloc - realloc implementation
 * @ptr: pointer to memory location
 * @size: represents old-size
 * @newsize: represents the new-size.
 * Return: on success, newly allocated memory
 */
void *my_realloc(void *ptr, unsigned int size, unsigned int newsize)
{
	void *result;

	if (newsize == size)
		return (ptr);
	if (newsize == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(newsize);
	if (result == NULL)
	{
		return (NULL);
	}
	if (ptr == NULL)
	{
		array_build(result, '\0', newsize);
		free(ptr);
	}
	else
	{
		mem_cpy(result, ptr, size);
		free(ptr);
	}
	return (result);
}
/**
 * mem_cpy - coipes memory
 * @dest: destination
 * @src: source
 * @i: memory bytes
 * Return: pointer to dest
 */
char *mem_cpy(char *dest, char *src, unsigned int i)
{
	unsigned int k;

	for (k = 0; k < i; k++)
	{
		dest[k] = src[k];
	}
	return (dest);
}
/**
 * mem_set - fills memory with bytes
 * @str: pointer to mem area
 * @bytes: constant byte
 * @i: first n bytes
 * Return: pointer to character
 */
char *mem_set(char *str, char bytes, unsigned int i)
{
	unsigned int k;

	for (k = 0; k < i; k++)
	{
		str[k] = bytes;
	}
	return (str);
}
