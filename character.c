#include "main.h"

/**
 * write_character - Writes a character to the buffer if space is available
 * @buf: The buffer to write to
 * @ch: The character to write
 * @remaining: The remaining space in the buffer
 * @written: Pointer to the number of characters written
 */
void write_character(char **buf, char ch, size_t *remaining, int *written)
{
	if (*remaining > 0)
	{
		*(*buf)++ = ch;
		(*written)++;
		(*remaining)--;
	}
}
