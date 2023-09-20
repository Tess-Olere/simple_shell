#include "shell.h"

/**
 * input_buf - This is the buffers chained commands.
 * @info: This is the parameter struct.
 * @buf: This is the address of the buffer.
 * @len: This is the address of len variable.
 * Return: The bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing is left in the buffer, fill it */
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* removes trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Thia gets a line minus the new line.
 * @info: This is the parameter struct
 * Return: The bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* this is the ';' command chain buffer */
	static size_t i, j, len;

	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + 1; /* It get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* this iterates to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* this increments past nulled ';'' */
		if (i >= len) /* did it reach the end of buffer? */
		{
			i = len = 0; /* to reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* to pass back pointer to current command position */
		return (_strlen(p)); /* this returns length of current command */
	}

	*buf_p = buf; /* if not a chain, pass buffer back from getline() */
	return (r); /* to return length of buffer from _getline() */
}

/**
 * read_buf - It reads a buffer
 * @info: The parameter struct
 * @buf: The buffer
 * @i: The size
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - This gets the next line of input from STDIN
 * @info: The parameter struct
 * @ptr: The address of pointer to buffer, preallocated or NULL
 * @length: This is the size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + 1, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - This blocks ctrl-C
 * @sig_num: This is the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$");
	_putchar(BUF_FLUSH);
}
