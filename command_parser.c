#include "main.h"

/**
 * parse_command_lines - Parse and execute command lines.
 * @shell: Shell structure.
 * @user_input: User input string.
 *
 * Return: 0 on exit, 1 to continue.
 */
int parse_command_lines(Shell *shell, char *user_input)
{
	int continue_execution;
	Separator *separator_head = NULL, *current_separator;
	CommandLine *command_line_head = NULL, *current_command_line;

	create_command_line_nodes(&separator_head, &command_line_head, user_input);
	current_separator = separator_head;
	current_command_line = command_line_head;

	for (; current_command_line != NULL;)
	{
		shell->user_input = current_command_line->cmd_line;
		shell->args = parse_command_line(shell->user_input);
		continue_execution = find_and_execute_command(shell);
		free(shell->args);

		if (continue_execution == 0)
		{
			break;
		}

		get_next_command_line(&current_separator, &current_command_line, shell);

		if (current_command_line != NULL)
		{
			current_command_line = current_command_line->next;
		}
	}

	free_separator(&separator_head);
	free_command_line(&command_line_head);

	switch (continue_execution)
	{
		case 0:
			return (0);

		default:
			return (1);
	}
}

/**
 * parse_command_line - Tokenize the input string into command line arguments.
 * @user_input: Input string.
 *
 * Return: Parsed command line arguments.
 */
char **parse_command_line(char *user_input)
{
	char **parsed_t;
	char *token;
	size_t i, buffer_size = 128;

	parsed_t = malloc((buffer_size) * sizeof(char *));
	if (parsed_t == NULL)
	{
		exit(EXIT_FAILURE);
	}

	token = custom_strtok(user_input, " \t\r\n\a");
	parsed_t[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buffer_size)
		{
			buffer_size = buffer_size + buffer_size;
			parsed_t = custom_reallocate_double_pointer(parsed_t, i, sizeof(char *));
			if (parsed_t == NULL)
			{
				exit(EXIT_FAILURE);
			}
		}

		token = custom_strtok(NULL, " \t\r\n\a");
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
 * Return: void, no return.
 */
void create_nodes(Separator **s_head, CommandLine **c_head, char *user_input)
{
	char *command_line;
	int i;

	user_input = remove_non_printed_characters(user_input);

	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == ';')
		{
			add_separator_at_end(s_head, user_input[i]);
		}
		if (user_input[i] == '|' || user_input[i] == '&')
		{
			add_separator_at_end(s_head, user_input[i]);
			i++;
		}
		i++;
	}

	command_line = custom_strtok(user_input, ";|&");
	do {
		command_line = remove_non_printed_characters2(command_line);
		add_command_line_at_end(c_head, command_line);
		command_line = custom_strtok(NULL, ";|&");
	} while (command_line != NULL);
}

/**
 * get_next_command_line - Get the next command line based on separators.
 * @set: Separator list.
 * @com: Command line list.
 * @shell: Shell structure.
 *
 * Return: void, no return.
 */
void get_next_command_line(Separator **set, CommandLine **com, Shell *shell)
{
	CommandLine *command_line = *com;
	Separator *separator = *set;
	int i, status = shell->shell_status;

	for (i = 1; i && separator != NULL;)
	{
		if (status == 0)
		{
			if (separator->sep == '&' || separator->sep == ';')
			{
				i = 0;
			}
			if (separator->sep == '|')
			{
				command_line = command_line->next;
				separator = separator->next;
			}
		}
		else
		{
			if (separator->sep == '|' || separator->sep == ';')
			{
				i = 0;
			}
			if (separator->sep == '&')
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

