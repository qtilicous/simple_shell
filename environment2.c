#include "main.h"

/**
 * set_cd_env_var - Set an environment variable for cd function.
 * @var_name: Environment variable name (e.g., pwd, oldpwd, home).
 * @var_value: Environment variable value.
 * @shell: Shell structure.
 *
 * Return: void, no return.
 */

void set_cd_env_var(char *var_name, char *var_value, Shell *shell)
{
	char *env_var, *env_name;
	int i = 0, cmp;

	while (shell->_environ[i])
	{
		env_var = custom_duplicate_string(shell->_environ[i]);
		env_name = custom_strtok(env_var, "=");
		cmp = custom_compare_strings(env_name, var_name);
		if (cmp == 0)
		{
			free(shell->_environ[i]);
			shell->_environ[i] = create_environment(env_name, var_value);
			free(env_var);
			return;
		}
		free(env_var);
		i++;
	}
	shell->_environ = custom_reallocate_memory(shell->_environ, i, (i + 2) * sizeof(char *));
	shell->_environ[i] = create_environment(var_name, var_value);
	shell->_environ[i + 1] = NULL;
}

/**
 * change_current_directory - Change the current directory to a user-specified directory.
 * @shell: Shell structure.
 *
 * Return: nothing.
 */

void change_current_directory(Shell *shell)
{
	char *dir, *_pwdp, *cdir;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	dir = shell->args[1];
	if (chdir(dir) == -1)
	{
		errors(shell, 2);
		return;
	}
	_pwdp = custom_duplicate_string(pwd);
	set_cd_env_var("OLDPWD", _pwdp, shell);
	cdir = custom_duplicate_string(dir);
	set_cd_env_var("PWD", cdir, shell);
	free(_pwdp);
	free(cdir);
	shell->shell_status = 0;
	chdir(dir);
}

/**
 * compare_env_varname - Compare environment variable names.
 * @variable_name: Name of the environment variable.
 * @partial_name: Partial name to compare.
 *
 * Return: 0 if not equal, i + 1 if equal.
 */

int compare_env_varname(const char *variable_name, const char *partial_name)
{
	int i = 0;

	while (variable_name[i] != '=')
	{
		if (variable_name[i] != partial_name[i])
			return (0);
		i++;
	}
	return (i + 1);
}

/**
 * get_cd_env_variable - Get an environment variable for cd.
 * @variable_name: Name of the environment variable.
 * @environment: Environment variable array.
 *
 * Return: Environment variable value, or NULL if not found.
 */

char *get_cd_env_variable(const char *variable_name, char **environment)
{
	char *env = NULL;
	int i = 0, j = 0;

	while (environment[i])
	{
		j = compare_env_varname(environment[i], variable_name);
		if (j)
		{
			env = environment[i];
			break;
		}
		i++;
	}
	return (env + j);
}
