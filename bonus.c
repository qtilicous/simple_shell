#include "main.h"

/**
 * rm_non_print - Replace non-printable characters with their codes.
 * @user_input: Input string.
 *
 * Return: Modified string.
 */

char *rm_non_print(char *user_input)
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
 * rest_non_print - Restore non-printable characters from their codes.
 * @user_input: Input string.
 *
 * Return: Restored string.
 */

char *rest_non_printable(char *user_input)
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
 * append_separator - Append a separator to the list.
 * @head: Head of the separator linked list.
 * @separator: Separator (; | &).
 *
 * Return: Pointer to the head.
 */

Separator *append_separator(Separator **head, char separator)
{
	Separator *new_node, *temp_node;

	new_node = malloc(sizeof(Separator));
	if (new_node == NULL)
		return (NULL);
	new_node->symbol = separator;
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
 * append_command - Append a command line to the list.
 * @head: Head of the command line linked list.
 * @cmd: Command line.
 *
 * Return: Pointer to the head.
 */

CommandLine *append_command(CommandLine **head, char *cmd)
{
	CommandLine *new_node, *temp_node;

	new_node = malloc(sizeof(CommandLine));
	if (new_node == NULL)
		return (NULL);
	new_node->line = cmd;
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
 * compare_cs - Chasr of strings comparison.
 * @string: Input string.
 * @delim: Delimiter.
 *
 * Return: 1 if they are equal, 0 if they are not.
 */

int compare_cs(char string[], const char *delim)
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
