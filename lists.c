#include "shell.h"

/**
 * add_node - adds a node to the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		{return (NULL); }

	_memset(new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
		new_node->str = _strdup(str);

	if (!*head)
		*head = new_node;
	else
	{
		list_t *node = *head;

		while (node->next)
			node = node->next;
		node->next = new_node;
	}

	{return (new_node); }
}

/**
 * print_and_free_list - prints and frees all nodes of a list
 * @head: address of pointer to head node
 *
 * Return: void
 */
void print_and_free_list(list_t **head)
{
	list_t *node = *head, *next_node;

	while (node)
	{
		_puts(node->str ? node->str : "(nil)");
		_puts("\n");

		next_node = node->next;
		free(node->str);
		free(node);

		node = next_node;
	}

	*head = NULL;
}
