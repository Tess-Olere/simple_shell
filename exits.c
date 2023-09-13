#include "shell.h"

/**
 * *_strncpy - This copies a string.
 * @dest: This is the destination of string to be copied to.
 * @src: This is the source string
 * @n: This is the amount of characters to be copied
 * Return: The concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - This concatenates two strings.
 * @dest: Thisis the first string.
 * @src: This is the second string
 * @n: This is the amount of bytes to be maximally used
 * Return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * *_strchr - This locates a character in a string.
 * @s: Thisis the string to be parsed.
 * @c: This is the character to find.
 * Return: (s) a pointer to the memory area s.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
