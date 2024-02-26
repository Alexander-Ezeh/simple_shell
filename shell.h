#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /*for  _printf*/
#include <unistd.h> /* for fork, _execve*/
#include <stdlib.h> /* for stdlib.h*/
#include <string.h> /* for  _strtok*/
#include <stddef.h> /* for stddef.h */
#include <errno.h> /* for error.h */
#include <sys/types.h> /* for types */
#include <sys/wait.h> /*for  wait.h */
#include <sys/stat.h> /* for  use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

#include "macros.h" /* for  msg prompt and help */

/**
 * _struct info- struct for program's data
 * @program_name: name of executable
 * @input_line: input pointer to be read by _getline
 * @command_name: first command typed by user
 * @exec_counter:the number of  excecuted commands
 * @file_descriptor: input of command in the  file descriptor
 * @tokens: tokenized input pointer array in the system
 * @env: environ
 * @alias_list: alias pointer array list.
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
 * struct builtins - builtin structure
 * @builtin: builtin name.
 * @function: function to be called for each of the  builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/*========  shell.c  ========*/

/* Inicializes struct with the  program info */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* infinite loop that shows prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Prints command in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========  _getline.c  ========*/

/* Reads line of standard input*/
int _getline(data_of_program *data);

/* splits each line for all  logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*======== expansions.c ========*/

/* expands variables */
void expand_variables(data_of_program *data);

/* expands aliases */
void expand_alias(data_of_program *data);

/* appends string to buffers end */
int buffer_add(char *buffer, char *str_to_add);


/*======== _strtok.c ========*/

/* Separates tokens string using designed delimiter */
void tokenize(data_of_program *data);

/* Create a  pointer to be part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Execute an entire path with command */
int execute(data_of_program *data);


/*======== builtins_2.c ========*/

/* If builtin match is found, execute it */
int builtins_list(data_of_program *data);


/*======== find.c ========*/

/* Creats array path directories */
char **tokenize_path(data_of_program *data);

/* Searchs for  programs in path */
int find_program(data_of_program *data);


/*======== helpers_free.c ========*/

/* Frees filled directories memory */
void free_array_of_pointers(char **directories);

/* Frees looped fields */
void free_recurrent_data(data_of_program *data);

/* Frees the data field */
void free_all_data(data_of_program *data);


/*======== builtins_3.c ========*/

/* Closes open shell */
int builtin_exit(data_of_program *data);

/* Changes are made to the current directory */
int builtin_cd(data_of_program *data);

/* sets working directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* shows all  information in  help */
int builtin_help(data_of_program *data);

/* sets, unsets and shows all aliases in code */
int builtin_alias(data_of_program *data);


/*======== builtins_1.c ========*/

/* Shows shell in the  running environment */
int builtin_env(data_of_program *data);

/* creates or overrides data in the  environemnt variable */
int builtin_set_env(data_of_program *data);

/* deletes all environment variable */
int builtin_unset_env(data_of_program *data);


/*======== env_management.c ========*/

/* Gets environment to manage  variable value */
char *env_get_key(char *name, data_of_program *data);

/* Overwrites all environment variable value*/
int env_set_key(char *key, char *value, data_of_program *data);

/* Removes all environment key*/
int env_remove_key(char *key, data_of_program *data);

/* prints the current woeking  environment */
void print_environ(data_of_program *data);


/*======== helpers_2.c ========*/

/* Prints standart output of the  string */
int _print(char *string);

/* Prints standard error of the  strin*/
int _printe(char *string);

/* Prints strings in standar error */
int _print_error(int errorcode, data_of_program *data);


/*======== helpers_4.c ========*/

/* Counts number of the characters in a string */
int str_length(char *string);

/* Duplicates string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverses string */
void str_reverse(char *string);


/*======== helpers_3.c ========*/

/* Casts int to a  string */
void long_to_string(long number, char *string, int base);

/* converts a string to a set of  number */
int _atoi(char *s);

/* counts the coincidences of character in a string */
int count_characters(char *string, char *character);


/*======== _alias.c ========*/

/* print all  list of alias */
int print_alias(data_of_program *data, char *alias);

/* gets the list of alias name */
char *get_alias(data_of_program *data, char *alias);

/* sets the alias names of lists */
int set_alias(char *alias_string, data_of_program *data);


#endif /* SHELL_H */
