#include "main.h"

/**
 * get_env_var - Get an environment variable value.
 * @var_name: Name of the environment variable.
 * @_env: Environment variable array.
 *
 * Return: Value of the environment variable.
 */
char *get_env_var(const char *var_name, char **_env)
{
	int i = 0, j = 0, found = 0;
	char *env_ptr = NULL;
	const char *cmp_env;

	while (_env[i])
	{
		cmp_env = _env[i];
		while (cmp_env[j] != '=')
		{
			if (cmp_env[j] != var_name[j])
			{
				found = 0;
				break;
			}
			found = j + 1;
			j++;
		}

		if (found)
		{
			env_ptr = _env[i];
			break;
		}

		i++;
	}
	return (env_ptr + found);

}

/**
 * print_env_var - Print environment variables.
 * @sh: Shell structure.
 *
 * Return: always 1 (success).
 */
int print_env_var(myshell *sh)
{
	int i = 0, j;

	while (sh->_env[i])
	{
		for (j = 0; sh->_env[i][j]; j++)
			;

		write(STDOUT_FILENO, sh->_env[i], j);
		write(STDOUT_FILENO, "\n", 1);

		i++;
	}

	sh->status = 0;
	return (1);
}

/**
 * _setenv - Set an environment variable.
 * @sh: Shell structure.
 *
 * Return: 1 on success, error message on failure.
 */
int _setenv(myshell *sh)
{
	myshell *shell_ptr;
	char *var_name, *var_value, *env_var, *env_name;
	int i, env_compare;

	if (sh->args[1] == NULL || sh->args[2] == NULL)
	{
		handle_errors(sh, -1);
		return (1);
	}

	var_name = sh->args[1];
	var_value = sh->args[2];
	shell_ptr = sh;

	i = 0;
	while (shell_ptr->_env[i])
	{
		env_var = duplicate_string(shell_ptr->_env[i]);
		env_name = tokenize_string(env_var, "=");
		env_compare = compare_strings(env_name, var_name);
		if (env_compare == 0)
		{
			free(shell_ptr->_env[i]);
			shell_ptr->_env[i] = create_env_var(var_name, var_value);
			free(env_var);
			return (1);
		}
		free(env_var);
		i++;
	}

	shell_ptr->_env = reallocate_dp(shell_ptr->_env, i, sizeof(char *) * (i + 2));
	shell_ptr->_env[i] = create_env_var(var_name, var_value);
	shell_ptr->_env[i + 1] = NULL;

	return (1);
}

/**
 * _unsetenv - Unset an environment variable.
 * @sh: Shell structure.
 *
 * Return: 1 on success or error message on failure.
 */
int _unsetenv(myshell *sh)
{
	char **env_rel;
	int i, j, check = -1;
	char *var_env;

	if (sh->args[1] == NULL)
	{
		handle_errors(sh, -1);
		return (1);
	}
	for (i = 0; sh->_env[i]; i++)
	{
		var_env = duplicate_string(sh->_env[i]);
		if (compare_strings(tokenize_string(var_env, "="), sh->args[1]) == 0)
		{
			check = i;
		}
		free(var_env);
	}
	if (check == -1)
	{
		handle_errors(sh, -1);
		return (1);
	}
	env_rel = malloc((i + 1) * sizeof(char *));
	if (env_rel == NULL)
	{
		free(env_rel);
		return (0);
	}
	for (i = j = 0; sh->_env[i]; i++)
	{
		if (i != check)
			env_rel[j++] = sh->_env[i];
	}
	env_rel[j] = NULL;
	free(sh->_env[check]);
	free(sh->_env);
	sh->_env = env_rel;
	return (1);
}

/**
 * create_env_var - Create a new environment variable.
 * @var_name: Name of the environment variable.
 * @var_value: Value of the environment variable.
 *
 * Return: New environment variable.
 */
char *create_env_var(char *var_name, char *var_value)
{
	char *create;
	int env = string_length(var_name), val = string_length(var_value);

	create = malloc((env + val + 2) * sizeof(char));
	if (create == NULL)
	{
		free(create);
		return (NULL);
	}

	copy_string(create, var_name);
	concatenate_strings(create, "=");
	concatenate_strings(create, var_value);
	concatenate_strings(create, "\0");
	return (create);
}
