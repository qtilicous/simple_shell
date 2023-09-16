#include "main.h"

/**
 * copy_string - Copy the source string to the destination.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *copy_string(char *dest, char *src)
{
	size_t i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * concatenate_strings - Concatenate two strings.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *concatenate_strings(char *dest, const char *src)
{
	int i, j = 0;

	for (i = 0; dest[i] != '\0'; i++)
		;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * duplicate_string - Duplicate a string in memory.
 * @str: Pointer to the original string.
 *
 * Return: Pointer to the duplicated string in memory.
 */
char *duplicate_string(const char *str)
{
	size_t str_length;
	char *new_str;

	str_length = string_length(str);

	new_str = malloc((str_length + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);

	copy_memory(new_str, str);

	return (new_str);
}

/**
 * compare_strings - Compare two strings.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 *
 * Return: 0 if both strings are equal, otherwise the difference.
 */
int compare_strings(char *s1, char *s2)
{
	int i = 0, diff = 0;

	while (diff == 0)
	{
		if ((s1[i] == '\0') && (s2[i] == '\0'))
			break;

		diff = *(s1 + i) - *(s2 + i);
		i++;
	}

	return (diff);
}

/**
 * tokenize_string - Tokenize a string using a delimiter.
 * @string: Input string.
 * @delimiter: Delimiter string.
 *
 * Return: Tokenized string.
 */
char *tokenize_string(char string[], const char *delimiter)
{
	unsigned int i, j;
	static char *token_start, *token_end;
	char *token;

	if (string != NULL)
	{
		if (compare_cs(string, delimiter))
			return (NULL);
		token_start = string;
		i = string_length(string);
		token_end = &string[i];
	}
	token = token_start;
	if (token == token_end)
		return (NULL);

	for (j = 0; *token_start; token_start++)
	{
		if (token_start != token)
		{
			if (*token_start && *(token_start - 1) == '\0')
				break;
		}
		for (i = 0; delimiter[i]; i++)
		{
			if (*token_start == delimiter[i])
			{
				*token_start = '\0';
				if (token_start == token)
					token++;
				break;
			}
		}
		if (*token_start && j == 0)
			j = 1;
	}
	if (j == 0)

		return (NULL);
	return (token);
}

