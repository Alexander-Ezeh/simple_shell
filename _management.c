/* #include "shell.h"

/**
 * _get_key - gets value of environment variable
 * key: environ variable of interest
 * data: program's data structure
 * Return: value of variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* validates arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains length of variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterate the environ and check for coincidence of same */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* return value of the key NAME=  when found*/
			return (data->env[i] + key_length + 1);
		}
	}
	/* returns NULL if not found */
	return (NULL);
}

/**
 * set_key - overwrites value of environ variable
 * or create it if does not exist.
 * key: name of variable to set
 * value: the new value
 * data: program's data structure
 * Return: 1 if parameters is NULL, 2 if there are error and 0 for sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	/* validates arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtain the length of variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterate the environ and check for coincidence of the same */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* If the key exists */
			is_new_key = 0;
			/* frees entire variable, its new created below */
			free(data->env[i]);
			break;
		}
	}
	/* makes string of form key=value */
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_a_new_key)
	{/* variable is new, it is created at end of list and we */
	/* insert NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * _remove_key - removes key from environ
 * key: key to remove
 * data: structure of program's data
 * Return: 1 if key is removed, 0 if key doesnt exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* validate argument */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtain the length of variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* iterates the environ and checks for coincidences */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* if key is existing, remove it */
			free(data->env[i]);

			/* move the other keys all in one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* insert NULL value at end of new list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * _environ - prints current environ
 * data: program data structure
 * Return: 0
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
} */
