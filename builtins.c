#include "main.h"

/**
 * change_directory - Change the current directory.
 * @sh: Shell structure.
 *
 * Return: Always 1 (success).
 */

int change_directory(shell_t *sh)
{
	char *d = sh->args[1];

	if (d == NULL || compare_strings(dir, "$HOME") == 0
			|| compare_strings(dir, "--") == 0)
	{
		home_dir(sh);
		return (1);
	}
	else if (compare_strings(d, "-") == 0)
	{
		previous_dir(sh);
		return (1);
	}
	cd(sh);
	return (1);
}

/**
 * previous_dir - Change the current directory to the previous directory.
 * @sh: Shell structure.
 *
 * Return: nothing.
 */
void previous_dir(shell_t *sh)
{
	char *current_dir, *old_dir, *current_pwd, *old_pwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	current_pwd = duplicate_string(pwd);
	old_dir = get_cd_env("OLDPWD", sh->_env);

	if (old_dir == NULL)
		old_pwd = current_pwd;
	else
		old_pwd = duplicate_string(old_current_directory);
	set_cd("OLDPWD", current_pwd, sh);
	switch (chdir(old_pwd))
	{
		case -1:
			set_cd("PWD", current_pwd, sh);
			break;
		default:
			set_cd("PWD", old_pwd, sh);
	}
	current_dir = get_cd_env("PWD", sh->_env);
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
 * @sh: Shell structure.
 *
 * Return: nothing.
 */
void home_dir(shell_t *sh)
{
	char current_dir[PATH_MAX];
	char *home_dir = get_cd_env("HOME", sh->_env);

	getcwd(current_dir, sizeof(current_dir));
	if (home_dir == NULL || chdir(home_dir) == -1)
		handle_errors(shell, 2);
	else
	{
		set_cd("OLDPWD", current_dir, sh);
		set_cd("PWD", home_directory, sh);
	}
	Sh->status = 0;
}

/**
 * get_builtin - Get the pointer to the specified builtin command.
 * @cmd: The command entered by the user.
 *
 * Return: Pointer to the corresponding builtin function.
 */
int (*get_builtin(char *cmd))(shell_t *)
{
	int i = 0, cmp;

	builtins_t builtins[] = {
		{"exit", shell_exit},
		{"env", print_env_var},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", change_directory},
		{NULL, NULL},
	}
	while (builtins[i].name)
	{
		cmp = compare_strings(builtins[i].name, cmd);
		if (cmp == 0)
			break;
		i++;
	}
	return (builtins[i].function);
}

/**
 * shell_exit - Exit the shell prompt.
 * @sh: Shell structure.
 *
 * Return: 0 on success, 1 on failure.
 */
int shell_exit(shell_t *sh)
{
	unsigned int st;
	int valid, length, num, should_exit;

	if (sh->args[1] != NULL)
		should_exit = 1;
	else
		should_exit = 0;
	if (should_exit)
	{
		valid = is_digit(sh->args[1]);
		st = string_to_integer(sh->args[1]);
		length = string_length(sh->args[1]);
		num = st > (unsigned int)INT_MAX;
		if (length > 10 || num || !valid)
		{
			handle_errors(sh, 2);
			sh->status = 2;
			return (1);
		}
		sh->status = (st % 256);
	}
	return (0);
}
