#include "main.h"

/**
 * find_execommand - Find and execute a command.
 * @sh: Shell structure.
 *
 * Return: 1 on success.
 */

int find_execommand(myshell *sh)
{
	int (*builtin_func)(myshell *sh);

	if (sh->args[0] == NULL)
		return (1);
	builtin_func = builtins(sh->args[0]);
	if (builtin_func != NULL)
		return (builtin_func(sh));
	return (execute_command(sh));
}

/**
 * execute_command - Execute a command.
 * @sh: Shell structure.
 *
 * Return: 1 on success.
 */

int execute_command(myshell *sh)
{
	int state, executable;
	pid_t _pid, _mypid;
	char *cmd_directory;

	UNUSED(_mypid);

	executable = is_exe(sh);
	switch (executable)
	{
		case 0:
			cmd_directory = find_command(sh->args[0], sh->_env);
			if (command_error(cmd_directory, sh) == 1)
				return (1);
			break;
		case -1:
			return (1);
	}
	_pid = fork();
	switch (_pid)
	{
		case 0:
			if (executable == 0)
				cmd_directory = find_command(sh->args[0], sh->_env);
			else
				cmd_directory = sh->args[0];
			execve(cmd_directory + executable, sh->args, sh->_env);
			break;
		case -1:
			perror(sh->av[0]);
			return (1);
		default:
			do {
				_mypid = waitpid(_pid, &state, WUNTRACED);
			} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	sh->status = state / 256;
	return (1);
}

/**
 * is_exe - Check if a file is executable.
 * @sh: Shell structure.
 *
 * Return: 0 if it's not an executable, otherwise returns the index.
 */

int is_exe(myshell *sh)
{
	int i = 0, j;
	char *user_input;
	struct stat s;

	user_input = sh->args[0];
	while (user_input[i])
	{
		if (user_input[i] == 46)
		{
			if (user_input[i + 1] == 46)
				return (0);
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
	if (stat(user_input + i, &s) == 0)
		return (i);
	handle_errors(sh, 127);
	return (-1);
}

/**
 * find_command - Find the location of a command.
 * @command: Command, e.g., ls.
 * @_env: Environment variable.
 *
 * Return: Location of the command or NULL if not found.
 */

char *find_command(char *command, char **_env)
{
	int index = 0, dirl, cmdl;
	char *pcmd, *pptr, *ptoken, *dir;
	struct stat s;

	pcmd = get_env_var("PATH", _env);
	if (pcmd)
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
