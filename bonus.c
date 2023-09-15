#include "main.h"

/**
 * remove_non_printable - Replace non-printable characters with their codes.
 * @user_input: Input string.
 *
 * Return: Modified string.
 */

char *remove_non_printable(char *user_input)
{
	int i = 0;

	while (user_input[i])
	{
		if (user_input[i] == '|')
		{
			if (user_input[i + 1] != '|')
				user_input[i] = 16;
			else
				i++;
		}
		if (user_input[i] == '&')
		{
			if (user_input[i + 1] != '&')
				user_input[i] = 12;
			else
				i++;
		}
		i++;
	}
	return (user_input);
}

/**
 * restore_non_printable - Restore non-printable characters from their codes.
 * @user_input: Input string.
 *
 * Return: Restored string.
 */

char *restore_non_printable(char *user_input)
{
	int i = 0;

	while (user_input[i])
	{
		user_input[i] = (user_input[i] == 16 ? '|' : user_input[i]);
		user_input[i] = (user_input[i] == 12 ? '&' : user_input[i]);
		i++;
	}
	return (user_input);
}

/**
 * append_separator_to_list - Append a separator to the list.
 * @head: Head of the separator linked list.
 * @separator: Separator (; | &).
 *
 * Return: Pointer to the head.
 */

separator_t *append_separator_to_list(separator_t **head, char separator)
{
	separator_t *new_node, *temp_node;

	new_node = malloc(sizeof(separator_t));
	if (new_node == NULL)
		return (NULL);
	new_node->sep = separator;
	new_node->next = NULL;
	temp_node = *head;
	if (temp_node == NULL)
		*head = new_node;
	else
	{
		while (temp_node->next != NULL)
		{
			temp_node = temp_node->next;
		}
		temp_node->next = new_node;
	}
	return (*head);
}

/**
 * append_command_line_to_list - Append a command line to the list.
 * @head: Head of the command line linked list.
 * @cmd: Command line.
 *
 * Return: Pointer to the head.
 */

cmdline_t *append_command_line_to_list(cmdline_t **head, char *cmd)
{
	cmdline_t *new_node, *temp_node;

	new_node = malloc(sizeof(cmdline_t));
	if (new_node == NULL)
		return (NULL);
	new_node->cmd_line = cmd;
	new_node->next = NULL;

	temp_node = *head;
	if (temp_node == NULL)
		*head = new_node;
	else
	{
		while (temp_node->next != NULL)
		{
			temp_node = temp_node->next;
		}
		temp_node->next = new_node;
	}
	return (*head);
}

/**
 * custom_strcmp - Custom string comparison.
 * @string: Input string.
 * @delim: Delimiter.
 *
 * Return: 1 if they are equal, 0 if they are not.
 */

int custom_strcmp(char string[], const char *delim)
{
	unsigned int i, j, k, l, m;

	l = 0;
	m = 0;
	for (i = 0, k = 0; string[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (string[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	l = i;
	m = k;
	if (l == m)
		return (1);
	return (0);
}
