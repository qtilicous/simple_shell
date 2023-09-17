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

char *rest_non_print(char *user_input)
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
 * @sep: Separator (; | &).
 *
 * Return: Pointer to the head.
 */

myseparator *append_separator(myseparator **head, char sep)
{
	myseparator *new, *temp;

	new = malloc(sizeof(myseparator));
	if (new == NULL)
		return (NULL);
	new->symbol = sep;
	new->next = NULL;
	temp = *head;
	if (temp == NULL)
		*head = new;
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (*head);
}

/**
 * append_commandl - Append a command line to the list.
 * @head: Head of the command line linked list.
 * @cl: Command line.
 *
 * Return: Pointer to the head.
 */

mycline *append_commandl(mycline **head, char *cl)
{
	mycline *new, *temp;

	new = malloc(sizeof(mycline));
	if (new == NULL)
		return (NULL);
	new->line = cl;
	new->next = NULL;

	temp = *head;
	if (temp == NULL)
		*head = new;
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (*head);
}

/**
 * compare_cs - Char of strings comparison.
 * @str: Input string.
 * @lim: Delimiter.
 *
 * Return: 1 if they are equal, 0 if they are not.
 */

int compare_cs(char str[], const char *lim)
{
	unsigned int i, j, k, l, m;

	l = 0;
	m = 0;
	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; lim[j]; j++)
		{
			if (str[i] == lim[j])
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
