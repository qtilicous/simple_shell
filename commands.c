#include "main.h"

/**
 * find_builtin_or_execute - Find and execute a command.
 * @shell: Shell structure.
 *
 * Return: 1 on success.
 */

int find_builtin_or_execute(Shell *shell)
{
	int (*builtin_func)(Shell *shell);

	if (shell->args[0] == NULL)
		return (1);
	builtin_func = find_builtin(shell->args[0]);
	if (builtin_func != NULL)
		return (builtin_func(shell));
	return (execute_command(shell));
}

/**
 * execute_command - Execute a command.
 * @shell: Shell structure.
 *
 * Return: 1 on success.
 */

int execute_command(Shell *shell)
{
	int shell_status, executable;
	pid_t pid, mypid;
	char *cmd_directory;

	UNUSED(mypid);

	executable = is_executable(shell);
	switch (executable)
	{
		case 0:
			cmd_directory = find_command_location(shell->args[0], shell->_environ);
			if (check_command_error(cmd_directory, shell) == 1)
				return (1);
			break;
		case -1:
			return (1);
	}
	pid = fork();
	switch (pid)
	{
		case 0:
			if (executable == 0)
				cmd_directory = find_command_location(shell->args[0], shell->_environ);
			else
				cmd_directory = shell->args[0];
			execve(cmd_directory + executable, shell->args, shell->_environ);
			break;
		case -1:
			perror(shell->av[0]);
			return (1);
		default:
			do {
				mypid = waitpid(pid, &shell_status, WUNTRACED);
			} while (!WIFEXITED(shell_status) && !WIFSIGNALED(shell_status));
	}
	shell->shell_status = shell_status / 256;
	return (1);
}

/**
 * is_executable - Check if a file is executable.
 * @shell: Shell structure.
 *
 * Return: 0 if it's not an executable, otherwise returns the index.
 */

int is_executable(Shell *shell)
{
	int i = 0, j;
	char *user_input;
	struct stat st;

	user_input = shell->args[0];
	while (user_input[i])
	{
		if (user_input[i] == 46)
		{
			if (user_input[i + 1] == 46)
				return (0)
			if (user_input[i + 1] == 47)
				continue;
			else
				break;
		}
		else if (user_input[i] == 47 && i != 0)
		{
			if (user_input[i + 1] == 46)
				continue;
			i++;
			break;
		}
		else
			break;
		i++;
	}
	j = i;
	if (j == 0)
		return (0);
	if (stat(user_input + i, &st) == 0)
		return (i);
	errors(shell, 127);
	return (-1);
}

/**
 * find_command_location - Find the location of a command.
 * @command: Command, e.g., ls.
 * @environment: Environment variable.
 *
 * Return: Location of the command or NULL if not found.
 */

char *find_command_location(char *command, char **environment)
{
	int index = 0, dir_len, cmd_len;
	char *cmd_path, *path_ptr, *path_token, *directory;
	struct stat st;

	cmd_path = get_env_var("PATH", environment);
	if (cmd_path)
	{
		path_ptr = custom_duplicate_string(cmd_path);
		cmd_len = custom_string_length(command);
		path_token = custom_tokenize_string(path_ptr, ":");

		for (; path_token != NULL;)
		{
			if (is_directory_path(cmd_path, &index))
			{
				if (stat(command, &st) == 0)
					return (command);
			}
			dir_len = custom_string_length(path_token);
			directory = malloc(cmd_len + 2 + dir_len);
			custom_copy_string(directory, path_token);
			custom_concatenate_strings(directory, "/");
			custom_concatenate_strings(directory, command);
			if (stat(directory, &st) == 0)
			{
				free(path_ptr);
				return (directory);
			}
			free(directory);
			path_token = custom_tokenize_string(NULL, ":");
		}
		free(path_ptr);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == 47)
	{
		if (stat(command, &st) == 0)
			return (command);
	}
	return (0);
}

/**
 * is_directory_path - Check if a path is a directory in the current directory.
 * @path: Pointer to the path.
 * @index: Pointer to the index.
 *
 * Return: 1 if the path is searchable in the current directory, 0 otherwise.
 */

int is_directory_path(char *path, int *index)
{
	if (path[*index] == 58)
		return (1);
	for (; path[*index] != 58 && path[*index];)
	{
		*index = *index + 1;
	}
	if (path[*index])
		*index = *index + 1;
	return (0);
}
