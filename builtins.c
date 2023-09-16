#include "main.h"

/**
 * change_directory - Change the current directory.
 * @shell: Shell structure.
 *
 * Return: Always 1 (success).
 */

int change_directory(Shell *shell)
{
	char *dir = shell-pargs[1];

	if (dir == NULL || compare_strings(dir, "$HOME") == 0
			|| compare_strings(dir, "--") == 0)
	{
		home_dir(shell);
		return (1);
	}
	else if (compare_strings(dir, "-") == 0)
	{
		previous_dir(shell);
		return (1);
	}
	cd(shell);
	return (1);
}

/**
 * previous_dir - Change the current directory to the previous directory.
 * @shell: Shell structure.
 *
 * Return: nothing.
 */
void previous_dir(Shell *shell)
{
	char *current_dir, *old_dir, *current_pwd, *old_pwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	current_pwd = duplicate_string(pwd);
	old_dir = get_cd_env("OLDPWD", shell->environment);

	if (old_dir == NULL)
		old_pwd = current_pwd;
	else
		old_pwd = duplicate_string(old_current_directory);
	set_cd("OLDPWD", current_pwd, shell);
	switch (chdir(old_pwd))
	{
		case -1:
			set_cd("PWD", current_pwd, shell);
			break;
		default:
			set_cd("PWD", old_pwd, shell);
	}
	current_dir = get_cd_env("PWD", shell->environment);
	write(STDOUT_FILENO, current_dir, string_length(current_dir));
	write(STDOUT_FILENO, "\n", 1);
	free(current_pwd);
	if (old_dir)
		free(old_pwd);
	Shell->status = 0;
	chdir(current_dir);
}

/**
 * home_dir - Change the current directory to the home directory.
 * @shell: Shell structure.
 *
 * Return: nothing.
 */
void home_dir(Shell *shell)
{
	char current_dir[PATH_MAX];
	char *home_dir = get_cd_env("HOME", shell->environment);

	getcwd(current_dir, sizeof(current_dir));
	if (home_dir == NULL || chdir(home_dir) == -1)
		handle_errors(shell, 2);
	else
	{
		set_cd("OLDPWD", current_dir, shell);
		set_cd("PWD", home_directory, shell);
	}
	Shell->status = 0;
}

/**
 * get_builtin - Get the pointer to the specified builtin command.
 * @command: The command entered by the user.
 *
 * Return: Pointer to the corresponding builtin function.
 */
int (*get_builtin(char *command))(Shell *)
{
	int i = 0, cmp;

	Builtins Builtins[] = {
		{"exit", shell_exit},
		{"env", print_env_var},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", change_directory},
		{NULL, NULL},
	}
	while (Builtins[i].name)
	{
		cmp = compare_strings(Builtins[i].name, command);
		if (cmp == 0)
			break;
		i++;
	}
	return (Builtins[i].function);
}

/**
 * shell_exit - Exit the shell prompt.
 * @shell: Shell structure.
 *
 * Return: 0 on success, 1 on failure.
 */
int shell_exit(Shell *shell)
{
	unsigned int st;
	int valid, length, num, should_exit;

	if (Shell->pargs[1] != NULL)
		should_exit = 1;
	else
		should_exit = 0;
	if (should_exit)
	{
		valid = is_digit(Shell->pargs[1]);
		st = string_to_integer(Shell->pargs[1]);
		length = string_length(Shell->pargs[1]);
		num = st > (unsigned int)INT_MAX;
		if (length > 10 || num || !valid)
		{
			handle_errors(shell, 2);
			shell->status = 2;
			return (1);
		}
		shell->status = (st % 256);
	}
	return (0);
}
