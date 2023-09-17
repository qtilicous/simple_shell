#include "main.h"

/**
 * exit_error - Generate an error message for shell exit.
 * @sh: Shell structure.
 *
 * Return: Error message.
 */
char *exit_error(myshell *sh)
{
	char *error, *str = integer_to_string(sh->line_count);
	int l = string_length(shell->av[0]) + string_length(str);

	len += string_length(sh->args[0]) + string_length(sh->args[1]) + 23;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(str);
			return (NULL);
	}

	copy_string(error, sh->av[0]);
	concatenate_strings(error, ": ");
	concatenate_strings(error, str);
	concatenate_strings(error, ": ");
	concatenate_strings(error, sh->args[0]);
	concatenate_strings(error, ": Illegal number: ");
	concatenate_strings(error, sh->args[1]);
	concatenate_strings(error, "\n\0");
	free(str);

	return (error);
}

/**
 * env_error - Generate an error message for environment variable error
 * @sh: Shell structure.
 *
 * Return: Error message.
 */
char *env_error(myshell *sh)
{
	char *error;
	char *s = integer_to_string(sh->line_count);
	char *message = ": Unable to add or change or remove env\n";
	int l;

	l = string_length(sh->av[0]) + string_length(s);
	l = l + string_length(sh->args[0]) + string_length(message) + 5;

	error = malloc((l + 1) * sizeof(char));
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
	concatenate_strings(error, message);
	concatenate_strings(error, "\0");
	free(s);

	return (error);
}

/**
 * handle_errors - Handle and display errors.
 * @sh: Shell structure.
 * @error: Error code.
 *
 * Return: Error code.
 */
int handle_errors(myshell *sh, int error)
{
	char *err;
	int check = compare_strings("cd", sh->args[0]);
	int exit = compare_strings("exit", sh->args[0]);

	if (error == 127)
	{
		err = not_found_error(sh);
	}
	if (error == 126)
	{
		err = path_error(sh);
	}
	if (error == -1)
	{
		err = env_error(sh);
	}
	if (error == 2)
		{
		if (check == 0)
		{
			err = cd_error(sh);
		}
		else if (exit == 0)
		{
			err = exit_error(sh);
		}
	}

	if (err)
	{
		write(STDERR_FILENO, err, string_length(err));
		free(err);
	}

	sh->status = error;

	return (error);
}

/**
 * command_error - Check for command execution errors.
 * @ddir: Pointer to the destination directory.
 * @sh: Shell structure.
 *
 * Return: 1 if there is an error, 0 if not.
 */
int command_error(char *ddir, myshell *sh)
{
	int i, j, k;

	if (ddir == NULL)
	{
		handle_errors(sh, 127);
			return (1);
	}

	i = compare_strings(sh->args[0], ddir);
	if (i != 0)
	{
		j = access(ddir, X_OK);
		if (j == -1)
		{
			handle_errors(sh, 126);
			free(ddir);
				return (1);
		}
		free(ddir);
	}
	else
	{
		k = access(sh->args[0], X_OK);
		if (k == -1)
		{
			handle_errors(sh, 126);
				return (1);
		}
	}

	return (0);
}

/**
 * not_found_error - Generate an error message for command not found.
 * @sh: Shell structure.
 *
 * Return: Error message.
 */
char *not_found_error(myshell *sh)
{
	char *error, *s = integer_to_string(sh->line_count);
	int str_length;

	str_length = string_length(sh->av[0]) + string_length(s);
	str_length = str_length + string_length(sh->args[0]) + 18;

	error = malloc((str_length + 1) * sizeof(char));
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
	concatenate_strings(error, ": not found\n");
	concatenate_strings(error, "\0");
	free(s);

	return (error);
}

