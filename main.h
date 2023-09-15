#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#define UNUSED(x) (void)(x)

extern char **custom_environment;

typedef struct Shell Shell;

typedef struct Builtins Builtins;

typedef struct Separator Separator;

typedef struct CommandLine CommandLine;

/**
* struct Shell - Structure representing the shell.
* @args: Command line arguments.
* @user_input: User's command input.
* @parsed_args: Parsed command line arguments.
* @status: Status of the shell.
* @line_count: Line counter.
* @environment: Environment variables.
* @pid_str: Process ID of the shell as a string.
*/

struct Shell
{
	char **args;
	char *user_input;
	char **parsed_args;
	char *pid_str;
	char **environment;
	int status;
	int line_count;
};

/**
* struct Builtins - Structure for shell built-in commands.
* @name: The name of the built-in command.
* @function: Pointer to the function implementing the command.
*/

struct Builtins
{
	char *name;
	int (*function)(Shell *shell);
};
/**
* struct CommandLine - Structure for a single linked list of command lines.
* @line: A command line node.
* @next: Pointer to the next node.
* Description: Single linked list to store command lines.
*/
struct CommandLine
{
	char *line;
	struct CommandLine *next;
};

/**
* struct Separator - Structure for a single linked list of separators.
* @symbol: The separator character (e.g., ';').
* @next: Pointer to the next node.
* Description: Single linked list to store separators.
*/
struct Separator
{
	char symbol;
	struct Separator *next;
};

/* scan.c */
char *read_user_input(int *eof);
/*function that reads the user input string*/
ssize_t custom_getline(char **outp_buffer, size_t *outp_size, FILE *inp_stream);
/*function that reads user input from stream.*/
void custom_getline2(char **buffer, size_t *s, char *s_buffer, size_t inpsize);
/*helper function for custom_getline(), that compares and assign the result to it.*/

/* strings1.c */
char *custom_copy_string(char *dest, char *src);
/*Copy the source string to the destination.*/
char *custom_concatenate_strings(char *dest, const char *src);
/*Concatenate two strings.*/
char *custom_duplicate_string(const char *str);
/*Duplicate a string in memory.*/
int custom_compare_strings(char *s1, char *s2);
/*Compare two strings.*/
char *custom_tokenize_string(char string[], const char *delimiter);
/*Tokenize a string using a delimiter.*/

/* strings2.c */
int custom_count_digits(const char *str);
/*Count the number of digits in an integer.*/
int custom_string_length(const char *str);
/*Get the length of a string.*/
char *custom_integer_to_string(int num);
/*Convert an integer to a string.*/
int custom_string_to_integer(char *str);
/*Convert a string to an integer.*/
int custom_is_digit(const char *character);
/*Check if a string represents a digit (0 through 9).*/

/* memory.c */
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int size);
/*Copy memory from source to destination.*/
void *reallocate_memory(void *old_ptr, unsigned int old_size, unsigned int new_size);
/*Reallocate memory.*/
char **reallocate_memory_double_pointer(char **old_double_ptr, unsigned int old_size, unsigned int new_size);
/*Reallocate memory for a double pointer.*/
void free_separator_list(Separator **head);
/*Free a separator singly linked list.*/
void free_command_line_list(CommandLine **head);
/*Free a command line singly linked list.*/

/* commands.c */
int find_builtin_or_execute(Shell *shell);
/*Find and execute a command.*/
int execute_command(Shell *shell);
/*Execute a command.*/
int is_executable(Shell *shell);
/*Check if a file is executable.*/
char *find_command_location(char *command, char **environment);
/*Find the location of a command.*/
int is_directory_path(char *path, int *index);
/*Check if a path is a directory in the current directory.*/

/* environment.c */
char *get_environment_variable(const char *variable_name, char **environment);
int print_environment_variables(Shell *shell);
int set_environment_variable(Shell *shell);
int unset_environment_variable(Shell *shell);
char *create_environment_variable(char *variable_name, char *variable_value);

/* environment2.c */
void change_directory(Shell *shell);
int compare_environment_variable(const char *variable_name, const char *partial_name);
char *get_cd_environment_variable(const char *variable_name, char **environment);
void set_cd_environment_variable(char *variable_name, char *variable_value, Shell *shell);

/* command_parser.c */
int parse_command(Shell *shell, char *user_input);
char **parse_command_line(char *user_input);
void create_command_line_node(Separator **separator_head, CommandLine **command_line_head, char *user_input);
void next_command_line(Separator **separator_list, CommandLine **command_line_list, Shell *shell);

/* bonus.c */
char *strip_non_printable_characters(char *user_input);
char *strip_non_printable_characters2(char *user_input);
Separator *append_separator_node(Separator **head, char separator);
CommandLine *append_command_line_node(CommandLine **head, char *command_line);
int custom_compare_string(char string[], const char *delimiter);

/* errors1.c */
int check_command_error(char *directory, Shell *shell);
int handle_errors(Shell *shell, int error);
char *command_not_found_error(Shell *shell);
char *environment_error(Shell *shell);
char *change_directory_error(Shell *shell);

/* errors2.c */
char *change_directory_error2(Shell *shell, char *message, char *error, char *path);
char *path_error(Shell *shell);
char *exit_error(Shell *shell);

/* builtins.c */
int (*find_builtin_command(char *command))(Shell *shell);
int exit_shell(Shell *shell);
int change_current_directory(Shell *shell);
void go_to_home_directory(Shell *shell);
void go_to_previous_directory(Shell *shell);

#endif

