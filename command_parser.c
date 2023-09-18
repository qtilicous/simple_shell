#include "main.h"

/**
 * parse_commandl - Parse and execute command lines.
 * @sh: Shell structure.
 * @user_input: User input string.
 *
 * Return: 0 on exit, 1 to continue.
 */
int parse_commandl(myshell *sh, char *user_input)
{
	int loop;
	myseparator *s_head = NULL, *s_current;
	mycline *c_head = NULL, *c_current;

	create_nodes(&s_head, &c_head, user_input);
	s_current = s_head;
	c_current = c_head;

	for (; c_current != NULL;)
	{
		sh->user_input = c_current->line;
		sh->args = toke_commandl(sh->user_input);
		loop = find_execommand(sh);
		free(sh->args);

		if (loop == 0)
		{
			break;
		}

		next_commandl(&s_current, &c_current, sh);

		if (c_current != NULL)
		{
			c_current = c_current->next;
		}
	}

	free_separator_list(&s_head);
	free_cline_list(&c_head);

	switch (loop)
	{
		case 0:
			return (0);

		default:
			return (1);
	}
}

/**
 * toke_commandl - Tokenize the input string into command line arguments.
 * @user_input: Input string.
 *
 * Return: Parsed command line arguments.
 */
char **toke_commandl(char *user_input)
{
	char **parsed_t;
	char *token;
	size_t i, buffer_size = 128;

	parsed_t = malloc((buffer_size) * sizeof(char *));
	if (parsed_t == NULL)
	{
		exit(EXIT_FAILURE);
	}

	token = tokenize_string(user_input, " \t\r\n\a");
	parsed_t[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buffer_size)
		{
			buffer_size = buffer_size + buffer_size;
			parsed_t = reallocate_dp(parsed_t, i, sizeof(char *));
			if (parsed_t == NULL)
			{
				exit(EXIT_FAILURE);
			}
		}

		token = tokenize_string(NULL, " \t\r\n\a");
		parsed_t[i] = token;
	}

	return (parsed_t);
}

/**
 * create_nodes - Create nodes for command lines and separators.
 * @s_head: Head of separator linked list.
 * @c_head: Head of command line linked list.
 * @user_input: User input string.
 *
 * Return: nothing.
 */
void create_nodes(myseparator **s_head, mycline **c_head, char *user_input)
{
	char *command_line;
	int j;

	user_input = rm_non_print(user_input);

	j = 0;
	while (user_input[j])
	{
		if (user_input[j] == ';')
		{
			append_separator(s_head, user_input[j]);
		}
		if (user_input[j] == '|' || user_input[j] == '&')
		{
			append_separator(s_head, user_input[j]);
			j++;
		}
		j++;
	}

	command_line = tokenize_string(user_input, ";|&");
	do {
		command_line = rest_non_print(command_line);
		append_commandl(c_head, command_line);
		command_line = tokenize_string(NULL, ";|&");
	} while (command_line != NULL);
}

/**
 * next_commandl - Get the next command line based on separators.
 * @set: Separator list.
 * @com: Command line list.
 * @sh: Shell structure.
 *
 * Return: Nothing.
 */
void next_commandl(myseparator **set, mycline **com, myshell *sh)
{
	mycline *command_line = *com;
	myseparator *separator = *set;
	int i, s = sh->status;

	for (i = 1; i && separator != NULL;)
	{
		if (s == 0)
		{
			if (separator->symbol == '&' || separator->symbol == ';')
			{
				i = 0;
			}
			if (separator->symbol == '|')
			{
				command_line = command_line->next;
				separator = separator->next;
			}
		}
		else
		{
			if (separator->symbol == '|' || separator->symbol == ';')
			{
				i = 0;
			}
			if (separator->symbol == '&')
			{
				command_line = command_line->next;
				separator = separator->next;
			}
		}
		if (!i && separator != NULL)
		{
			separator = separator->next;
		}
	}
	*set = separator;
	*com = command_line;
}

