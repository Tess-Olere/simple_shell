#include "shell.h"

/**
 * is_cmd - This helps to detrmine if a file is an
 * executable command
 * @info: This is the info struct
 * @path: This is the path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if(!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - This duplicates characters
 * @pathstr: This is the PATH string
 * @start: The starting index
 * @stop: The stopping index
 * Return: The pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int 1 =0, k = 0;

	for (k = 0, i = start; i <stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - This helps to find the cmd in the PATH string
 * @info: This is the info string.
 * @pathstr: This is the PATH string.
 * @cmd: This is the cmd to find.
 * Return: The full path of cmd if found or NULL
 */
char *find_path(info
		_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (1pathstr)
		return (NULL);
	if ((_strlrn(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars (pathstr, curr_pos, i);
			if (!path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
