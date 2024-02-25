#include "shell.h"

/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int a, b, counter = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (a = 0; data->input_line[a]; a++)
	{
		for (b = 0; delimiter[b]; b++)
		{
			if (data->input_line[a] == delimiter[b])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	a = 0;
	data->tokens[a] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[a++])
	{
		data->tokens[a] = str_duplicate(_strtok(NULL, delimiter));
	}
}
