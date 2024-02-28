#include "shell.h"

/**
 * builtin_env - shows environs in which shell runs
 * @data: program's data structure
 * Return: 0 if sucess, or any number declared in arguments
 */
int builtin_env(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{/* check chars = */
			if (data->tokens[1][i] == '=')
			{/* checks var with the same name and change its value*/

				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + i + 1, data);

				/* print environ */
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{/* prints variables if it doesnt exist in the environ */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* returns old value of the variable*/
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - NULL
 * @data: structucture for the program's data
 * Return: 0 if sucess, or any number declared in arguments
 */
int builtin_set_env(data_of_program *data)
{
	/* validate arguements */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - NULL
 * @data: program's data structure
 * Return: always NULL
 */
int builtin_unset_env(data_of_program *data)
{
	/* validates args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}

