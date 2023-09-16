#include "main.h"

/**
 * change_directory_error - Print an error message for change directory error
 * @shell: Shell structure.
 *
 * Return: Error message.
 */
char *change_directory_error(Shell *shell)
{
	char *err, *message, *str = custom_itoa(shell->line_counter);
	int id, len;

	if (shell->args[1][0] == '-')
	{
		message = ": Not a legal option ";
		id = 2;
	}
	else
	{
		message = ": can't cd to given directory ";
		id = custom_strlen(shell->args[1]);
	}

	len = custom_strlen(shell->av[0]) + custom_strlen(shell->args[0]);
	len = len + custom_strlen(str) + custom_strlen(message) + id + 6;

	err = malloc((len + 1) * sizeof(char));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}

	err = change_directory_error2(shell, message, err, str);
	free(str);

	return (err);
}

/**
 * cd_error_concat - Concatenate the error message for cd_error.
 * @shell: Shell structure.
 * @message: Message to show to the user.
 * @error: Output message.
 * @line: Line of string.
 *
 * Return: Error message.
 */
char *cd_error_concat(Shell *shell, char *message, char *error, char *line)
{
	char *invalid;

	custom_strcpy(error, shell->av[0]);
	custom_strcat(error, ": ");
	custom_strcat(error, line);
	custom_strcat(error, ": ");
	custom_strcat(error, shell->args[0]);
	custom_strcat(error, message);

	if (shell->args[1][0] == '-')
	{
		invalid = malloc(3);
		invalid[0] = '-';
		invalid[1] = shell->args[1][1];
		invalid[2] = '\0';
		custom_strcat(error, invalid);
		free(invalid);
	}
	else
	{
		custom_strcat(error, shell->args[1]);
	}

	custom_strcat(error, "\n");
	custom_strcat(error, "\0");
	return (error);
}

/**
 * path_error_message - Generate an error message for path_error.
 * @shell: Shell structure.
 *
 * Return: Error message.
 */
char *path_error_message(Shell *shell)
{
	char *error, *str = custom_itoa(shell->line_counter);
	int len = custom_strlen(shell->av[0]) + custom_strlen(str);

	len = len + custom_strlen(shell->args[0]) + 25;

	error = malloc((len + 1) * sizeof(char));
	if (error == 0)
	{
		free(error);
		free(str);
		return (NULL);
	}

	custom_strcpy(error, shell->av[0]);
	custom_strcat(error, ": ");
	custom_strcat(error, str);
	custom_strcat(error, ": ");
	custom_strcat(error, shell->args[0]);
	custom_strcat(error, ": Permission denied\n");
	custom_strcat(error, "\0");
	free(str);

	return (error);
}

