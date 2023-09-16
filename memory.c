#include "main.h"

/**
 * copy_memory - Copy memory from source to destination.
 * @dest_ptr: Destination pointer.
 * @src_ptr: Source pointer.
 * @size: Size of the memory to copy.
 *
 * Return: Nothing.
 */
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int size)
{
	char *dest = (char *)dest_ptr;
	char *src = (char *)src_ptr;

	unsigned int i = 0;

	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}
/**
 * reallocate_mem - Reallocate memory.
 * @ptr: Pointer to the previously allocated memory.
 * @old: Size, in bytes, of the old memory block.
 * @nw: New size, in bytes, of the memory block.
 *
 * Return: If nw == old, returns ptr.
 * If reallocation fails, returns NULL.
 */
void *reallocate_mem(void *ptr, unsigned int old, unsigned int nw)
{
	void *nwm_ptr;

	if (ptr == NULL)
	{
		return (malloc(nw));
	}
	if (nw == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (nw == old)
	{
		return (ptr);
	}
	nwm_ptr = malloc(nw);
	if (nwm_ptr == NULL)
	{
		return (NULL);
	}
	if (nw < old)
	{
		copy_memory(nwm_ptr, ptr, nw);
	}
	else
	{
		copy_memory(nwm_ptr, ptr, old);
	}
	free(ptr);
	return (nwm_ptr);
}

/**
 * free_separator_list - Free a separator singly linked list.
 * @start: Head of the linked list.
 *
 * Return: Nothing.
 */
void free_separator_list(separator_t **start)
{
	separator_t *current, *temp;

	if (start != NULL)
	{
		current = *start;

		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}

		*start = NULL;
	}
}

/**
 * free_cline_list - Free a command line singly linked list.
 * @start: Head of the linked list.
 *
 * Return: void, no return.
 */
void free_cline_list(cline_t **start)
{
	cline_t *current, *temp;

	if (start != NULL)
	{
		current = *start;

		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}

		*start = NULL;
	}
}

/**
 * reallocate_dp - Reallocate memory for a double pointer.
 * @old_dp: Double pointer to the previously allocated memory.
 * @old: Size, in bytes, of the old memory block.
 * @nw: New size, in bytes, of the memory block.
 *
 * Return: If nw == old, returns old_double_ptr without changes.
 * If reallocation fails, returns NULL.
 */
char **reallocate_dp(char **old_dp, unsigned int old, unsigned int nw)
{
	unsigned int i;
	char **nwm_dp;

	if (old_dp == NULL)
	{
		return (malloc(nw * sizeof(char *)));
	}

	if (nw == old)
	{
		return (old_dp);
	}

	nwm_dp = malloc(nw * sizeof(char *));
	if (nwm_dp == NULL)
	{
		return (NULL);
	}

	i = 0;
	while (i < old)
	{
		nwm_dp[i] = old_dp[i];
		i++;
	}

	free(old_dp);

	return (nwm_dp);
}

