#include "main.h"

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
 * set_cd - Set an environment variable for cd function.
 * @var_name: Environment variable name (e.g., pwd, oldpwd, home).
 * @var_value: Environment variable value.
 * @shell: Shell structure.
 *
 * Return: Nothing.
 */

void set_cd(char *var_name, char *var_value, Shell *shell)
{
	char *env_var, *env_name;
	int i = 0, cmp;

	while (shell->_env[i])
	{
		env_var = duplicate_string(shell->_env[i]);
		env_name = tokenize_string(env_var, "=");
		cmp = compare_strings(env_name, var_name);
		if (cmp == 0)
		{
			free(shell->_env[i]);
			shell->_env[i] = create_env_var(env_name, var_value);
			free(env_var);
			return;
		}
		free(env_var);
		i++;
	}
	shell->_env = reallocate_dp(shell->_env, i, (i + 2) * sizeof(char *));
	shell->_env[i] = create_env_var(var_name, var_value);
	shell->_env[i + 1] = NULL;
}

/**
 * cd - Change the current directory
 * @shell: Shell structure.
 *
 * Return: Nothing.
 */

void cd(Shell *shell)
{
	char *dir, *_pwdp, *cdir;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	dir = shell->pargs[1];
	if (chdir(dir) == -1)
	{
		handle_errors(shell, 2);
		return;
	}
	_pwdp = duplicate_string(pwd);
	set_cd("OLDPWD", _pwdp, shell);
	cdir = duplicate_string(dir);
	set_cd("PWD", cdir, shell);
	free(_pwdp);
	free(cdir);
	shell->status = 0;
	chdir(dir);
}


/**
 * get_cd_env - Get an environment variable for cd.
 * @variable_name: Name of the environment variable.
 * @environment: Environment variable array.
 *
 * Return: Environment variable value, or NULL if not found.
 */

char *get_cd_env(const char *variable_name, char **environment)
{
	char *e = NULL;
	int i = 0, j = 0;

	while (environment[i])
	{
		j = compare_env_varname(environment[i], variable_name);
		if (j)
		{
			e = environment[i];
			break;
		}
		i++;
	}
	return (e + j);
}
