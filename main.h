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
ssize_t custom_getline(char **outp_buffer, size_t *outp_size, FILE *inp_stream);
void custom_getline2(char **buffer, size_t *s, char *s_buffer, size_t inpsize);

/* strings1.c */
char *custom_copy_string(char *dest, char *src);
char *custom_concatenate_strings(char *dest, const char *src);
char *custom_duplicate_string(const char *str);
int custom_compare_strings(char *s1, char *s2);
char *custom_tokenize_string(char string[], const char *delimiter);

/* strings2.c */
int custom_count_digits(const char *str);
int custom_string_length(const char *str);
char *custom_integer_to_string(int num);
int custom_string_to_integer(char *str);
int custom_is_digit(const char *character);

/* memory.c e */
void custom_copy_memory(void *dest_ptr, const void *src_ptr, unsigned int size);
void *custom_reallocate_memory(void *ptr, unsigned int old, unsigned int new);
void custom_free_separator_list(separator_t **head);
void custom_free_command_line_list(cmdline_t **head);

/* commands.c */
int find_executable_command(Shell *shell;
int execute_command(Shell *shell);
int is_command_executable(Shell *shell);
char *find_command_location(char *command, char **environment);
int is_directory_path(char *path, int *index);

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

