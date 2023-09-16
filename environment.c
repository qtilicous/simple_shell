#include "main.h"

/**
 * get_env_var - Get an environment variable value.
 * @var_name: Name of the environment variable.
 * @env: Environment variable array.
 *
 * Return: Value of the environment variable.
 */
char *get_env_var(const char *var_name, char **env)
{
	int i = 0, j = 0, found = 0;
	char *env_ptr = NULL;
	const char *cmp_env;

	while (env[i])
	{
		cmp_env = env[i];
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
			env_ptr = env[i];
			break;
		}

		i++;

		return (env_ptr + found);
	}
}

/**
 * print_env_var - Print environment variables.
 * @shell: Shell structure.
 *
 * Return: 1 on success.
 */
int print_env_var(Shell *shell)
{
	int i = 0, j;

	while (shell->_environ[i])
	{
		for (j = 0; shell->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, shell->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);

		i++;
	}

	shell->shell_status = 0;
	return (1);
}

/**
 * _setenv - Set an environment variable.
 * @shell: Shell structure.
 *
 * Return: 1 on success, error message on failure.
 */
int _setenv(Shell *shell)
{
	Shell *shell_ptr;
	char *var_name, *var_value, *env_var, *env_name;
	int i, env_compare;

	if (shell->args[1] == NULL || shell->args[2] == NULL)
	{
		errors(shell, -1);
		return (1);
	}

	var_name = shell->args[1];
	var_value = shell->args[2];
	shell_ptr = shell;

	i = 0;
	while (shell_ptr->_environ[i])
	{
		env_var = custom_duplicate_string(shell_ptr->_environ[i]);
		env_name = custom_strtok(env_var, "=");
		env_compare = custom_compare_strings(env_name, var_name);
		if (env_compare == 0)
		{
			free(shell_ptr->_environ[i]);
			shell_ptr->_environ[i] = create_environment(var_name, var_value);
			free(env_var);
			return (1);
		}
		free(env_var);
		i++;
	}

	shell_ptr->_environ = reallocate_dp(shell_ptr->_environ, i, sizeof(char *) * (i + 2));
	shell_ptr->_environ[i] = create_environment(var_name, var_value);
	shell_ptr->_environ[i + 1] = NULL;

	return (1);
}

/**
 * _unsetenv - Unset an environment variable.
 * @shell: Shell structure.
 *
 * Return: 1 on success, error message on failure.
 */
int _unsetenv(Shell *shell)
{
	char **env_rel;
	int i, j, check = -1;
	char *var_env;

	if (shell->args[1] == NULL)
	{
		errors(shell, -1);
		return (1);
	}
	for (i = 0; shell->_environ[i]; i++)
	{
		var_env = custom_duplicate_string(shell->_environ[i]);
		if (custom_compare_strings(custom_strtok(var_env, "="), shell->args[1]) == 0)
		{
			check = i;
		}
		if (check == -1)
		{
			errors(shell, -1);
			return (1);

		}
		env_rel = malloc((i + 1) * sizeof(char *));
		if (env_rel == NULL)
		{
			free(env_rel);
			return (0);
		}
		for (i = j = 0; shell->_environ[i]; i++)
		{
			if (i != check)
				env_rel[j++] = shell->_environ[i];
		}
		env_rel[j] = NULL;
		free(shell->_environ[check]);
		free(shell->_environ);
		shell->_environ = env_rel;

		return (1);
	}
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
	int env = custom_string_length(var_name), val = custom_string_length(var_value);

	create = malloc((env + val + 2) * sizeof(char));
	if (create == NULL)
	{
		free(create);
		return (NULL);
	}

	custom_copy_string(create, var_name);
	custom_concatenate_strings(create, "=");
	custom_concatenate_strings(create, var_value);

	return (create);
}

