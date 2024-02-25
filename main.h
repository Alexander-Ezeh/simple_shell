#ifndef MAIN_H
#define MAIN_H

#include <stdio.h> /* _printf*/
#include <unistd.h> /* fork, _execve*/
#include <stdlib.h>
#include <string.h> /* _strtok*/
#include <stddef.h>
#include <errno.h> /* error */
#include <sys/types.h> /* type pid */
#include <sys/wait.h> /* wait */
#include <sys/stat.h> /* use of stat function */
#include <signal.h> /* signal management */
#include <fcntl.h> /* open files*/

#include "macros.h" /* msg prompt and help */

/**
 * struct info - struct for the program's data
 * @program_name: name of the executable
 * @input_line: input pointer to read _getline
 * @command_name: first command typed by the user
 * @exec_counter: excecuted number of commands
 * @file_descriptor: input of commands file descriptor
 * @tokens: tokenized input pointer array
 * @env: environ copy
 * @alias_list: alias pointer array.
 */

typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - builtin struct
 * @builtin: builtin name
 * @function: function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/*========  shell.c  ========*/

/* Inicializes struct with program info */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Prints in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Reads line of the standar input*/
int _getline(data_of_program *data);

/* splits each line for logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expands the  variables */
void expand_variables(data_of_program *data);

/* expands the  aliases */
void expand_alias(data_of_program *data);

/* appends the string to buffers end */
int buffer_add(char *buffer, char *str_to_add);


/*======== _strtok.c ========*/

/* Separates tokens string using a designed delimiter */
void tokenize(data_of_program *data);

/* Create pointer to be part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute entire path with command */
int execute(data_of_program *data);


/*======== builtins_2.c ========*/

/* If builtin is a match, execute it */
int builtins_list(data_of_program *data);


/*======== find.c ========*/

/* Create an array path directories */
char **tokenize_path(data_of_program *data);

/* Searchs programs in path */
int find_program(data_of_program *data);


/*======== helpers_free.c ========*/

/* Frees directories memory */
void free_array_of_pointers(char **directories);

/* Free loop fields */
void free_recurrent_data(data_of_program *data);

/* Free data field */
void free_all_data(data_of_program *data);


/*======== builtins_3.c ========*/

/* Closes shell */
int builtin_exit(data_of_program *data);

/* Changes current directory */
int builtin_cd(data_of_program *data);

/* sets work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* shows information help */
int builtin_help(data_of_program *data);

/* sets, unsets and shows aliases */
int builtin_alias(data_of_program *data);


/*======== builtins_1.c ========*/

/* Shows shell running environment */
int builtin_env(data_of_program *data);

/* creates or overrides environemnt variable */
int builtin_set_env(data_of_program *data);

/* deletes environment variable */
int builtin_unset_env(data_of_program *data);


/*======== env_management.c ========*/

/* Gets environment variable value */
char *env_get_key(char *name, data_of_program *data);

/* Overwrites environment variable value*/
int env_set_key(char *key, char *value, data_of_program *data);

/* Removes environment key*/
int env_remove_key(char *key, data_of_program *data);

/* prints the current environment */
void print_environ(data_of_program *data);


/*======== helpers_2.c ========*/

/* Prints standart output  string */
int _print(char *string);

/* Prints standard error string */
int _printe(char *string);

/* Prints strings in the standar error */
int _print_error(int errorcode, data_of_program *data);


/*======== helpers_4.c ========*/

/* Counts number of characters in a string */
int str_length(char *string);

/* Duplicate a string */
char *str_duplicate(char *string);

/* Compare two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenate two strings */
char *str_concat(char *string1, char *string2);

/* Reverses a string */
void str_reverse(char *string);


/*======== helpers_3.c ========*/

/* Casts int to string */
void long_to_string(long number, char *string, int base);

/* converts a string to a number */
int _atoi(char *s);

/* count coincidences of character in a string */
int count_characters(char *string, char *character);


/*======== _alias.c ========*/

/* print list of alias */
int print_alias(data_of_program *data, char *alias);

/* gets the alias name */
char *get_alias(data_of_program *data, char *alias);

/* sets the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif /* MAIN_H */
