#include "shell.h"

/**
 * builtins_list - search for match and executes associate builtin
 * @data: program's data structure
 * Return: Returns the function executed if there is a match,
 * else returns -1.
 */
int builtins_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*walks through the structure*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*if matched between given command and builtin,*/
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
/*executes the function, and return value of function*/
			return (options[iterator].function(data));
		}
/*if no match is found return -1 */
	}
	return (-1);
}

