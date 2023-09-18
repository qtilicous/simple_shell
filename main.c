#include "main.h"

/**
 * cmd_c - Handle the cmd + c.
 * @cmdc: Signal handler.
 *
 * Return: Nothing.
 */
void cmd_c(int cmdc)
{
	UNUSED(cmdc);
	write(STDIN_FILENO, "\n#simpleshell$ ", 15);
}

/**
 * rem_com - remove comments.
 * @s: input string.
 *
 * Return: output without comments.
 */
char *rem_com(char *s)
{
	int i = 0, j = 0, k;

	while (s[i])
	{
		if (s[i] == '#')
		{
			if  (i == 0)
			{
				free(s);
				return (NULL);
			}
			if (s[i - 1] == ' ')
				j = i;
			if (s[i - 1] == ';'  || s[i - 1] == '\t')
				j = i;
		}
		i++;
	}

	k = j;
	if (k != 0)
	{
		s = reallocate_mem(s, i, k + 1);
		s[k] = '\0';
	}
	return (s);
}

/**
 * shell_ini - Initialize shell structure.
 * @sh: shell structure.
 * @av: command line arguments.
 *
 * Return: Nothing.
 */
void shell_ini(myshell *sh, char **av)
{
	unsigned int j;

	sh->av = av;
	sh->status = 0;
	sh->user_input = NULL;
	sh->line_count = 1;
	sh->args = NULL;

	j = 0;
	while (environ[j])
	{
		j++;
	}
	sh->_env = malloc((j + 1) * sizeof(char *));

	j = 0;
	while (environ[j])
	{
		sh->_env[j] = duplicate_string(environ[j]);
		j++;
	}

	sh->_env[j] = NULL;
	sh->pid_str = integer_to_string(getpid());
}

/**
 * main - Entry point
 * @ac: command line arguments number (unused).
 * @av: command line arguments.
 *
 * Return: status.
 */
int main(int ac, char **av)
{
	myshell sh, *s;
	char *_input;
	int loop, eof;
	unsigned int i = 0;

	UNUSED(ac);
	shell_ini(&sh, av);
	signal(SIGINT, cmd_c);
	s = &sh;
	for (loop = 1; loop == 1;)
	{
		write(STDIN_FILENO, "#simpleshell$ ", 14);
		_input = read_input(&eof);
		if (eof != EOF)
		{
			_input = rem_com(_input);
			if (_input == NULL)
				continue;
			loop = parse_commandl(s, _input);
			s->line_count += 1;
			free(_input);
		}
		else
		{
			loop = 0;
			free(_input);
		}
	}
	for (i = 0; s->_env[i]; i++)
		free(s->_env[i]);
	free(s->pid_str);
	free(s->_env);
	switch (sh.status)
	{
		case -1:
			return (255);
		default:
			return (sh.status);
	}
}
