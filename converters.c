#include "main.h"

/**
 * count_digits - Count the number of digits in an integer.
 * @num: Input integer.
 *
 * Return: Number of digits in the integer.
 */

int count_digits(int num)
{
	int digit_count = 1;
	unsigned int absolute_num;

	if (num < 0)
	{
		digit_count++;
		absolute_num = num * -1;
	}
	else
		absolute_num = num;
	while (absolute_num > 9)
	{
		digit_count++;
		absolute_num = absolute_num / 10;
	}

	return (digit_count);
}

/**
 * string_length - Get the length of a string.
 * @str: Pointer to a string of characters.
 *
 * Return: Length of the string.
 */

int string_length(const char *str)
{
	int str_length = 0;

	while (str[str_length] != '\0')
		str_length++;
	return (str_length);
}

/**
 * integer_to_string - Convert an integer to a string.
 * @num: Input integer.
 *
 * Return: Converted integer as a string.
 */

char *integer_to_string(int num)
{
	char *string_buffer;
	unsigned int absolute_num;
	int digit_count = count_digits(num);

	string_buffer = malloc((digit_count + 1) * sizeof(char));
	if (string_buffer == NULL)
		return (NULL);
	string_buffer[digit_count] = 0;
	if (num < 0)
	{
		absolute_num = num * -1;
		string_buffer[0] = '-';
	}
	else
		absolute_num = num;
	digit_count--;
	do {
		string_buffer[digit_count] = (absolute_num % 10) + '0';
		absolute_num = absolute_num / 10;
		digit_count--;
	} while (absolute_num > 0);
	return (string_buffer);
}

/**
 * string_to_integer - Convert a string to an integer.
 * @str: Input string.
 *
 * Return: Integer value.
 */

int string_to_integer(char *str)
{
	unsigned int length_count = 0, size = 0, i = 0, j = 1, k = 1, l;

	while (*(str + length_count) != 0)
	{
		if (size > 0 && (*(str + length_count) < '0' || *(str + length_count) > '9'))
			break;
		if (*(str + length_count) == '-')
			j *= -1;
		if ((*(str + length_count) >= '0') && (*(str + length_count) <= '9'))
		{
			if (size > 0)
				k *= 10;
			size++;
		}
		length_count++;
	}
	for (l = length_count - size; l < length_count; l++)
	{
		i = i + ((*(str + l) - '0') * k);
		k /= 10;
	}
	return (i * j);
}

/**
 * is_digit - Check if a string represents a digit (0 through 9).
 * @character: Input character.
 *
 * Return: 1 if the character is a digit, 0 otherwise.
 */

int is_digit(const char *character)
{
	unsigned int j = 0;

	while (character[j])
	{
		if (character[j] < 48 || character[j] > 57)
			return (0);
		j++;
	}
	return (1);
}
