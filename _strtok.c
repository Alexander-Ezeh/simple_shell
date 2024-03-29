#include "main.h"
/**
 * _strtok - to separate string with known delimiters
 * @line: It is a pointer to the array we receive in the _getline.
 * @delim: It is characters we mark off in the string in parts.
 * Return: to the created token
*/
char *_strtok(char *line, char *delim)
{
	int i;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
				break;
		}
		if (delim[i] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			{
			*str = '\0';
			str++;
			return (copystr);
			}
		}
	}
	return (copystr);
}

