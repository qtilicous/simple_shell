#include "main.h"

/**
 * cd_error - Print an error message for change directory error
 * @sh: Shell structure.
 *
 * Return: Error message.
 */
char *cd_error(myshell *sh)
{
	char *error, *message, *s = integer_to_string(sh->line_count);
	int id, l;

	if (sh->args[1][0] == '-')
	{
		message = ": Not a legal option ";
		id = 2;
	}
	else
	{
		message = ": can't cd to given directory ";
		id = string_length(sh->args[1]);
	}

	l = string_length(sh->av[0]) + string_length(sh->args[0]);
	l = l + string_length(s) + string_length(message) + id + 6;

	error = malloc((l + 1) * sizeof(char));
	if (error == 0)
	{
		free(s);
		return (NULL);
	}

	error = cd_error_concat(sh, message, error, s);
	free(s);

	return (error);
}

/**
 * cd_error_concat - Concatenate the error message for cd_error.
 * @sh: Shell structure.
 * @message: Message to show to the user.
 * @error: Output message.
 * @line: Line of string.
 *
 * Return: Error message.
 */
char *cd_error_concat(myshell *sh, char *message, char *error, char *line)
{
	char *i;

	copy_string(error, sh->av[0]);
	concatenate_strings(error, ": ");
	concatenate_strings(error, line);
	concatenate_strings(error, ": ");
	concatenate_strings(error, sh->args[0]);
	concatenate_strings(error, message);

	if (sh->args[1][0] == '-')
	{
		i = malloc(3);
		i[0] = '-';
		i[1] = sh->args[1][1];
		i[2] = '\0';
		concatenate_strings(error, i);
		free(i);
	}
	else
	{
		concatenate_strings(error, sh->args[1]);
	}

	concatenate_strings(error, "\n");
	concatenate_strings(error, "\0");
	return (error);
}

/**
 * path_error - Generate an error message for path_error.
 * @sh: Shell structure.
 *
 * Return: Error message.
 */
char *path_error(myshell *sh)
{
	char *error, *s = integer_to_string(sh->line_count);
	int l = string_length(sh->av[0]) + string_length(s);

	l = l + string_length(sh->args[0]) + 25;

	error = malloc((len + 1) * sizeof(char));
	if (error == 0)
	{
		free(error);
		free(s);
		return (NULL);
	}

	copy_string(error, sh->av[0]);
	concatenate_strings(error, ": ");
	concatenate_strings(error, s);
	concatenate_strings(error, ": ");
	concatenate_strings(error, sh->args[0]);
	concatenate_strings(error, ": Permission denied\n");
	concatenate_strings(error, "\0");
	free(s);

	return (error);
}

