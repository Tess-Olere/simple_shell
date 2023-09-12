#include "shell.h"

/**
 * _myhistory - Displays the history type, one command by line and
 * preceded with line numbers starting at 0 (zero).
 * @info: The structure containing potential arguement used to
 * maintain constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - It sets alias to string
 * @info: The parameter struct
 * @str: The string alias
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _stchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(nfo->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - It stets alias to string.
 * @info: The parameter struct.
 * @str: The string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - It prints an alias string
 * @node: The alias node.
 * Return: Always 0 on success and 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
* _myalias - It mimics the alias builtin (man alias)
* @info: The structure containing the potential arguments. It is
* used to maintain constant functio prototype.
* Return: Always 0.
*/
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
