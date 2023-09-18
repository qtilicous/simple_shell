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
 * @sh: Shell structure.
 *
 * Return: Nothing.
 */

void set_cd(char *var_name, char *var_value, myshell *sh)
{
	char *evar, *ename;
	int i = 0, cmp;

	while (sh->_env[i])
	{
		evar = duplicate_string(sh->_env[i]);
		ename = tokenize_string(evar, "=");
		cmp = compare_strings(ename, var_name);
		if (cmp == 0)
		{
			free(sh->_env[i]);
			sh->_env[i] = create_env_var(ename, var_value);
			free(evar);
			return;
		}
		free(evar);
		i++;
	}
	sh->_env = reallocate_dp(sh->_env, i, (i + 2) * sizeof(char *));
	sh->_env[i] = create_env_var(var_name, var_value);
	sh->_env[i + 1] = NULL;
}

/**
 * cd - Change the current directory
 * @sh: Shell structure.
 *
 * Return: Nothing.
 */

void cd(myshell *sh)
{
	char *dir, *p, *c;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	dir = sh->args[1];
	if (chdir(dir) == -1)
	{
		handle_errors(sh, 2);
		return;
	}
	p = duplicate_string(pwd);
	set_cd("OLDPWD", p, sh);
	c = duplicate_string(dir);
	set_cd("PWD", c, sh);
	free(p);
	free(c);
	sh->status = 0;
	chdir(dir);
}

/**
 * get_cd_env - Get an environment variable for cd.
 * @var_name: Name of the environment variable.
 * @_env: Environment variable array.
 *
 * Return: Environment variable value, or NULL if not found.
 */

char *get_cd_env(const char *var_name, char **_env)
{
	char *e = NULL;
	int i = 0, j = 0;

	while (_env[i])
	{
		j = compare_env_varname(_env[i], var_name);
		if (j)
		{
			e = _env[i];
			break;
		}
		i++;
	}
	return (e + j);
}
