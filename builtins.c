#include "main.h"

/**
 * change_directory - Change the current directory.
 * @shell: Shell structure.
 *
 * Return: Always 1 (success).
 */

int change_directory(shell_t *shell)
{
	char *dir = shell->args[1];

	if (dir == NULL || strcmp(dir, "$HOME") == 0 || strcmp(dir, "--") == 0)
	{
		home_dir(shell);
		return (1);
	}
	else if (strcmp(dir, "-") == 0)
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
void previous_dir(shell_t *shell)
{
	char *current_dir, *old_dir, *current_pwd, *old_pwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	current_pwd = custom_strdup(pwd);
	old_dir = get_environment("OLDPWD", shell->environment);

	if (old_dir == NULL)
		old_pwd = current_pwd;
	else
		old_pwd = custom_strdup(old_current_directory);
	update_environment("OLDPWD", current_pwd, shell);
	switch (chdir(old_pwd))
	{
		case -1:
			update_environment("PWD", current_pwd, shell);
			break;
		default:
			update_environment("PWD", old_pwd, shell);
	}
	current_dir = get_environment("PWD", shell->environment);
	write(STDOUT_FILENO, current_dir, custom_strlen(current_dir));
	write(STDOUT_FILENO, "\n", 1);
	free(current_pwd);
	if (old_dir)
		free(old_pwd);
	shell->shell_status = 0;
	chdir(current_dir);
}

/**
 * home_dir - Change the current directory to the home directory.
 * @shell: Shell structure.
 *
 * Return: nothing.
 */
void home_dir(shell_t *shell)
{
	char current_dir[PATH_MAX];
	char *home_dir = get_environment("HOME", shell->environment);

	getcwd(current_dir, sizeof(current_dir));
	if (home_dir == NULL || chdir(home_dir) == -1)
		errors(shell, 2);
	else
	{
		update_environment("OLDPWD", current_dir, shell);
		update_environment("PWD", home_directory, shell);
	}
	shell->shell_status = 0;
}

/**
 * get_builtin - Get the pointer to the specified builtin command.
 * @command: The command entered by the user.
 *
 * Return: Pointer to the corresponding builtin function.
 */
int (*get_builtin(char *command))(shell_t *)
{
	int i = 0, cmp;

	builtin_t builtins[] = {
		{"exit", shell_exit},
		{"env", print_environment},
		{"setenv", set_environment},
		{"unsetenv", unset_environment},
		{"cd", change_directory},
		{NULL, NULL},
	}
	while (builtins[i].name)
	{
		cmp = custom_strcmp(builtins[i].name, command);
		if (cmp == 0)
			break;
		i++;
	}
	return (builtins[i].function);
}

/**
 * shell_exit - Exit the shell prompt.
 * @shell: Shell structure.
 *
 * Return: 0 on success, 1 on failure.
 */
int shell_exit(shell_t *shell)
{
	unsigned int status;
	int valid, length, num, should_exit;

	if (shell->args[1] != NULL)
		should_exit = 1;
	else
		should_exit = 0;
	if (should_exit)
	{
		valid = custom_isdigit(shell->args[1]);
		status = custom_atoi(shell->args[1]);
		length = custom_strlen(shell->args[1]);
		num = status > (unsigned int)INT_MAX;
		if (length > 10 || num || !valid)
		{
			errors(shell, 2);
			shell->shell_status = 2;
			return (1);
		}
		shell->shell_status = (status % 256);
	}
	return (0);
}
