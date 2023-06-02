#include "main.h"
/**
 * tokenize - tokenizes a string with a delimiter
 * @str: string to tokenize
 * @delimiter: delimiter to tokenize along eg space
 * Return: array of pointers to the tokens
 */
char **tokenize(char *str, char *delimiter)
{
	char **tokens = NULL;
	size_t token_count = 0, cap = 10;
	char *token;
	char **new_tokens;

	if (str == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * cap);
	if (tokens == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	while (1)
	{
		token = _strtok(str, delimiter);
		if (token == NULL)
			break;
		tokens[token_count++] = token;
		if (token_count == cap)
		{
			cap *= 2;
			new_tokens = my_realloc(tokens, sizeof(char *) * cap, sizeof(char *) * cap);
			if (new_tokens == NULL)
			{
				perror("Memory reallocation error");
				return (NULL);
			}
			tokens = new_tokens;
		}
		str = NULL;/*setting str to null to tokenize*/
	}
	return (tokens);
}
