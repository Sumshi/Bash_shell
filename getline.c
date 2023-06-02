#include "main.h"
/**
 * my_getline - getline implementation
 * @data: data to be read
 * Return: characters read
 */
ssize_t my_getline(main_t *data)
{
	char *cursor_ptr, *end_ptr, c;
	size_t size = BUFFER_SIZE, read_line, length, new_size;

	data->line = malloc(size * sizeof(char));
	if (data->line == NULL)
	{
		return (FAIL);
	}
	if (isatty(STDIN_FILENO))
	{
		PRINT(PROMPT);
	}
	for (cursor_ptr = data->line, end_ptr = data->line + size;;)
	{
		read_line = read(STDIN_FILENO, &c, 1);
		if (read_line == 0)
		{
			return (FAIL);
		}
		*cursor_ptr++ = c;
		if (c == '\n')
		{
			*cursor_ptr = '\0';
			return (SUCCESS);
		}
		if (cursor_ptr + 2 >= end_ptr)
		{
			new_size = size * 2;
			length = cursor_ptr - data->line;
			data->line = my_realloc(data->line, size * sizeof(char),
					new_size * sizeof(char));
			if (data->line == NULL)
			{
				return (FAIL);
			}
			size = new_size;
			end_ptr = data->line + size;
			cursor_ptr = data->line + length;
		}
	}
}
