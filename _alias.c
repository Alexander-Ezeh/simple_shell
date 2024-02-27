#include "shell.h"

/**
 * _alias - to add, remove or show aliases
 * data: program's data structure
 * alias: name of alias to be printed
 * Return: 0 if sucess, or any number declared in argument
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * _alias - add, remove or show aliases
 * data: program's data structure
 * name: name of requested alias.
 * Return: 0 if sucess, or any number declared in arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	/* validates arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{/* Iterates  environ and check for coincidence of varname */
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{/* returns value of the key NAME=  when found */
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	/* returns NULL when not found */
	return (NULL);

}

/**
 * _alias - to add, or override aliases
 * alias_string: the alias to be seted the form (name='value')
 * data: program's data structure
 * Return: 0 if sucess, or any number  declared in arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validates arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterate the alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* searches the value of  alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* Iterates alias list and check for coincidence of varname */
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{/* if alias exist */
			free(data->alias_list[j]);
			break;
		}

	/* adds alias */
	if (temp)
	{/* if alias exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /* if there is no alias */
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}

