#include "main.h"

/**
 * find_execommand - Find and execute a command.
 * @shell: Shell structure.
 *
 * Return: 1 on success.
 */

int find_execommand(Shell *shell)
{
	int (*builtin_func)(Shell *shell);

	if (shell->pargs[0] == NULL)
		return (1);
	builtin_func = get_builtin(shell->pargs[0]);
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

	executable = is_exe(shell);
	switch (executable)
	{
		case 0:
			cmd_directory = find_command(shell->pargs[0], shell->_env);
			if (command_error(cmd_directory, shell) == 1)
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
				cmd_directory = find_command(shell->pargs[0], shell->_env);
			else
				cmd_directory = shell->pargs[0];
			execve(cmd_directory + executable, shell->pargs, shell->_env);
			break;
		case -1:
			perror(shell->args[0]);
			return (1);
		default:
			do {
				mypid = waitpid(pid, &shell_status, WUNTRACED);
			} while (!WIFEXITED(shell_status) && !WIFSIGNALED(shell_status));
	}
	shell->status = shell_status / 256;
	return (1);
}

/**
 * is_exe - Check if a file is executable.
 * @shell: Shell structure.
 *
 * Return: 0 if it's not an executable, otherwise returns the index.
 */

int is_exe(Shell *shell)
{
	int i = 0, j;
	char *user_input;
	struct stat stat;

	user_input = shell->pargs[0];
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
	if (stat(user_input + i, &stat) == 0)
		return (i);
	errors(shell, 127);
	return (-1);
}

/**
 * find_command - Find the location of a command.
 * @command: Command, e.g., ls.
 * @environment: Environment variable.
 *
 * Return: Location of the command or NULL if not found.
 */

char *find_command(char *command, char **env)
{
	int index = 0, dirl, cmdl;
	char *pcmd, *pptr, *ptoken, *dir;
	struct stat s;

	pcmd = get_env_var("PATH", env);
	if (cmd_path)
	{
		pptr = duplicate_string(pcmd);
		cmdl = string_length(command);
		ptoken = tokenize_string(pptr, ":");

		for (; ptoken != NULL;)
		{
			if (is_dir_path(pcmd, &index))
			{
				if (stat(command, &s) == 0)
					return (command);
			}
			dirl = string_length(ptoken);
			dir = malloc(cmdl + 2 + dirl);
			copy_string(dir, ptoken);
			concatenate_strings(dir, "/");
			concatenate_strings(dir, command);
			if (stat(dir, &s) == 0)
			{
				free(pptr);
				return (dir);
			}
			free(dir);
			ptoken = tokenize_string(NULL, ":");
		}
		free(pptr);
		if (stat(command, &s) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == 47)
	{
		if (stat(command, &s) == 0)
			return (command);
	}
	return (0);
}

/**
 * is_dir_path - Check if a path is a directory in the current directory.
 * @path: Pointer to the path.
 * @index: Pointer to the index.
 *
 * Return: 1 if the path is searchable in the current directory, 0 otherwise.
 */

int is_dir_path(char *path, int *index)
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
