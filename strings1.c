#include "main.h"

/**
 * custom_copy_string - Copy the source string to the destination.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *custom_copy_string(char *dest, char *src)
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
 * custom_concatenate_strings - Concatenate two strings.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *custom_concatenate_strings(char *dest, const char *src)
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
 * custom_duplicate_string - Duplicate a string in memory.
 * @str: Pointer to the original string.
 *
 * Return: Pointer to the duplicated string in memory.
 */
char *custom_duplicate_string(const char *str)
{
	size_t str_length;
	char *new_str;

	str_length = custom_string_length(str);

	new_str = malloc((str_length + 1) * sizeof(char));
	if (new_str == NULL)
	{
		return (NULL);
	}

	custom_copy_string(new_str, str);

	return (new_str);
}

/**
 * custom_compare_strings - Compare two strings.
 * @s1: Pointer to the first string.
 * @s2: Pointer to the second string.
 *
 * Return: 0 if both strings are equal, otherwise the difference.
 */
int custom_compare_strings(char *s1, char *s2)
{
	int i = 0, diff = 0;

	while (diff == 0)
	{
		if ((s1[i] == '\0') && (s2[i] == '\0'))
		{
			break;
		}

		diff = s1[i] - s2[i];
		i++;
	}

	return (diff);
}

/**
 * custom_tokenize_string - Tokenize a string using a delimiter.
 * @input_string: Input string.
 * @delimiter: Delimiter string.
 *
 * Return: Tokenized string.
 */
char *custom_tokenize_string(char input_string[], const char *delimiter)
{
	unsigned int i, j;
	static char *token_start, *token_end;
	char *token;

	if (input_string != NULL)
	{
		if (custom_charcmp(input_string, delimiter))
			return (NULL);
		token_start = input_string;
		i = custom_string_length(input_string);
		token_end = &input_string[i];
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

