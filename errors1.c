#include "main.h"

/**
 * exit_error_message - Generate an error message for exit shell.
 * @shell: Shell structure.
 *
 * Return: Error message.
 */
char *exit_error_message(Shell *shell)
{
	char *error, *str = custom_itoa(shell->line_counter);
	int len = custom_strlen(shell->av[0]) + custom_strlen(str);

	len += custom_strlen(shell->args[0]) + custom_strlen(shell->args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(str);
			return (NULL);
	}

	custom_strcpy(error, shell->av[0]);
	custom_strcat(error, ": ");
	custom_strcat(error, str);
	custom_strcat(error, ": ");
	custom_strcat(error, shell->args[0]);
	custom_strcat(error, ": Illegal number: ");
	custom_strcat(error, shell->args[1]);
	custom_strcat(error, "\n\0");
	free(str);

	return (error);
}

/**
 * environment_error - Generate an error message for environment variable error
 * @shell: Shell structure.
 *
 * Return: Error message.
 */
char *environment_error(Shell *shell)
{
	char *err;
	char *str = custom_itoa(shell->line_counter);
	char *message = ": Unable to add or change or remove env\n";
	int len;

	len = custom_strlen(shell->av[0]) + custom_strlen(str);
	len = len + custom_strlen(shell->args[0]) + custom_strlen(message) + 5;

	err = malloc((len + 1) * sizeof(char));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}

	custom_strcpy(err, shell->av[0]);
	custom_strcat(err, ": ");
	custom_strcat(err, str);
	custom_strcat(err, ": ");
	custom_strcat(err, shell->args[0]);
	custom_strcat(err, message);
	custom_strcat(err, "\0");
	free(str);

	return (err);
}

/**
 * handle_errors - Handle and display errors.
 * @shell: Shell structure.
 * @error: Error code.
 *
 * Return: Error code.
 */
int handle_errors(Shell *shell, int error)
{
	char *err;
	int cd_check = custom_strcmp("cd", shell->args[0]);
	int exit_check = custom_strcmp("exit", shell->args[0]);

	if (error == 127)
	{
		err = command_not_found_error(shell);
	}
	if (error == 126)
	{
		err = environment_error(shell);
	}
	if (error == -1)
	{
		err = change_directory_error(shell);
	}
	if (error == 2)
		{
		if (cd_check == 0)
		{
			err = change_directory_error(shell);
		}
		else if (exit_check == 0)
		{
			err = exit_error(shell);
		}
	}

	if (err)
	{
		write(STDERR_FILENO, err, custom_strlen(err));
		free(err);
	}

	shell->shell_status = error;

	return (error);
}

/**
 * check_command_error - Check for command execution errors.
 * @directory: Pointer to the destination directory.
 * @shell: Shell structure.
 *
 * Return: 1 if there is an error, 0 if not.
 */
int check_command_error(char *directory, Shell *shell)
{
	int i, j, k;

	if (directory == NULL)
	{
		handle_errors(shell, 127);
			return (1);
	}

	i = custom_strcmp(shell->args[0], directory);
	if (i != 0)
	{
		j = access(directory, X_OK);
		if (j == -1)
		{
			handle_errors(shell, 126);
			free(directory);
				return (1);
		}
		free(directory);
	}
	else
	{
		k = access(shell->args[0], X_OK);
		if (k == -1)
		{
			handle_errors(shell, 126);
				return (1);
		}
	}

	return (0);
}

/**
 * command_not_found_error - Generate an error message for command not found.
 * @shell: Shell structure.
 *
 * Return: Error message.
 */
char *command_not_found_error(Shell *shell)
{
	char *err, *str = custom_itoa(shell->line_counter);
	int str_length;

	str_length = custom_strlen(shell->av[0]) + custom_strlen(str);
	str_length = str_length + custom_strlen(shell->args[0]) + 18;

	err = malloc((str_length + 1) * sizeof(char));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}

	custom_strcpy(err, shell->av[0]);
	custom_strcat(err, ": ");
	custom_strcat(err, str);
	custom_strcat(err, ": ");

	custom_strcat(err, shell->args[0]);
	custom_strcat(err, ": not found\n");
	custom_strcat(err, "\0");
	free(str);

	return (err);
}

