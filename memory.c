#include "main.h"

/**
 * custom_copy_memory - Copy memory from source to destination.
 * @dest_ptr: Destination pointer.
 * @src_ptr: Source pointer.
 * @size: Size of the memory to copy.
 *
 * Return: void, no return.
 */
void custom_copy_memory(void *dest_ptr, const void *src_ptr, unsigned int size)
{
	char *dest = (char *)dest_ptr;
	const char *src = (const char *)src_ptr;

	unsigned int i = 0;

	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}
/**
 * custom_reallocate_memory - Reallocate memory.
 * @ptr: Pointer to the previously allocated memory.
 * @old: Size, in bytes, of the old memory block.
 * @nw: New size, in bytes, of the memory block.
 *
 * Return: If nw == old, returns ptr.
 * If reallocation fails, returns NULL.
 */
void *custom_reallocate_memory(void *ptr, unsigned int old, unsigned int nw)
{
	unsigned int i;
	char **new_double_ptr;

	if (old_double_ptr == NULL)
	{
		return (malloc(nw * sizeof(char *)));
	}
	if (nw == old)
	{
		return (old_double_ptr);
	}

	new_double_ptr = malloc(nw * sizeof(char *));
	if (new_double_ptr == NULL)
	{
		return (NULL);
	}

	i = 0;
	while (i < old)
	{
		new_double_ptr[i] = old_double_ptr[i];
		i++;
	}

	free(old_double_ptr);

	return (new_double_ptr);
}

/**
 * custom_free_separator_list - Free a separator singly linked list.
 * @head: Head of the linked list.
 *
 * Return: void, no return.
 */
void custom_free_separator_list(separator_t **head)
{
	separator_t *current_node, *temp_node;

	if (head != NULL)
	{
		current_node = *head;

		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}

		*head = NULL;
	}
}

/**
 * custom_free_command_line_list - Free a command line singly linked list.
 * @head: Head of the linked list.
 *
 * Return: void, no return.
 */
void custom_free_command_line_list(cmdline_t **head)
{
	cmdline_t *current_node, *temp_node;

	if (head != NULL)
	{
		current_node = *head;

		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}

		*head = NULL;
	}
}

/**
 * reallocate_dp - Reallocate memory for a double pointer.
 * @old_double_ptr: Double pointer to the previously allocated memory.
 * @old: Size, in bytes, of the old memory block.
 * @nw: New size, in bytes, of the memory block.
 *
 * Return: If nw == old, returns old_double_ptr without changes.
 * If reallocation fails, returns NULL.
 */
char **reallocate_dp(char **old_double_ptr, unsigned int old, unsigned int nw)
{
	unsigned int i;
	char **new_double_ptr;

	if (old_double_ptr == NULL)
	{
		return (malloc(nw * sizeof(char *)));
	}

	if (nw == old)
	{
		return (old_double_ptr);
	}

	new_double_ptr = malloc(nw * sizeof(char *));
	if (new_double_ptr == NULL)
	{
		return (NULL);
	}

	i = 0;
	while (i < old)
	{
		new_double_ptr[i] = old_double_ptr[i];
		i++;
	}

	free(old_double_ptr);

	return (new_double_ptr);
}

