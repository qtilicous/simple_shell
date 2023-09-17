#include "main.h"

/**
 * _getline - Read user input from a stream.
 * @outp_buffer: Buffer to store user input.
 * @outp_size: Size of the buffer.
 * @inp_stream: Input stream (e.g., stdin).
 *
 * Return: Number of bytes read.
 */

ssize_t _getline(char **outp_buffer, size_t *outp_size, FILE *inp_stream)
{
	char *temp_buffer;
	char last_char = 'z';
	static ssize_t inp_size;
	ssize_t ret_value;
	int input_char;

	if (inp_size == 0)
		fflush(inp_stream);
	else
		return (-1);

	inp_size = 0;
	temp_buffer = malloc(sizeof(char) * 1024);
	if (temp_buffer == 0)
		return (-1);
	for (; last_char != '\n';)
	{
		input_char = read(STDIN_FILENO, &last_char, 1);
		if (input_char == -1 || (input_char == 0 && inp_size == 0))
		{
			free(temp_buffer);
			return (-1);
		}
		if (inp_size != 0 && input_char == 0)
		{
			inp_size++;
			break;
		}
		if (inp_size >= 1024)
			temp_buffer = reallocate_mem(temp_buffer, inp_size, inp_size + 1);
		temp_buffer[inp_size] = last_char;
		inp_size++;
	}
	temp_buffer[inp_size] = '\0';
	_getline2(outp_buffer, outp_size, temp_buffer, inp_size);
	ret_value = inp_size;
	if (input_char != 0)
		inp_size = 0;
	return (ret_value);
}

/**
 * _getline2 - Helper function for custom_getline(), compares and assigns
 * the result.
 * @buffer: Pointer to the buffer storing user input.
 * @s: Pointer to the size of the user input line.
 * @s_buffer: String of characters in the line.
 * @inpsize: Size of the user input buffer.
 *
 * Return : Nothing
 */

void _getline2(char **buffer, size_t *s, char *s_buffer, size_t inpsize)
{
	if (*s < inpsize)
	{
		if (inpsize > 1024)
			*s = inpsize;
		else
			*s = 1024;
		*buffer = s_buffer;
	}
	else if (*buffer == NULL)
	{
		if (inpsize > 1024)
			*s = inpsize;
		else
			*s = 1024;
		*buffer = s_buffer;
	}
	else
	{
		copy_string(*buffer, s_buffer);
		free(s_buffer);
	}
}

/**
 * read_input - Read user input.
 * @eof: Pointer to the end-of-file indicator.
 *
 * Return: User input string.
 */

char *read_input(int *eof)
{
	size_t size;
	char *input;

	size = 0;
	input = NULL;

	*eof = _getline(&input, &size, stdin);
	return (input);
}
