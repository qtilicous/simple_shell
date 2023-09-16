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

extern char **envment;

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
	char **pargs;
	char *pid_str;
	char **_env;
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
char *read_input(int *eof);
ssize_t _getline(char **outp_buffer, size_t *outp_size, FILE *inp_stream);
void _getline2(char **buffer, size_t *s, char *s_buffer, size_t inpsize);

/* strings1.c */
char *copy_string(char *dest, char *src);
char *concatenate_strings(char *dest, const char *src);
char *duplicate_string(const char *str);
int compare_strings(char *s1, char *s2);
char *tokenize_string(char string[], const char *delimiter);

/* strings2.c */
int count_digits(const char *str);
int string_length(const char *str);
char *integer_to_string(int num);
int string_to_integer(char *str);
int is_digit(const char *character);

/* memory.c */
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int size);
void *reallocate_mem(void *ptr, unsigned int old, unsigned int nw);
void free_separator_list(Separator **head);
void free_command_line_list(CommandLine **head);
char **reallocate_dp(char **old_dp, unsigned int old, unsigned int nw);


/* commands.c */
int find_execommand(Shell *shell);
int execute_command(Shell *shell);
int is_commandexe(Shell *shell);
char *find_command(char *command, char **env);
int is_dir_path(char *path, int *index);

/* environment.c */
char *get_env_var(const char *var_name, char **env);
int print_env_var(Shell *shell);
int _setenv(Shell *shell);
int _unsetenv(Shell *shell);
char *create_env_var(char *var_name, char *var_value);

/* environment2.c */
void set_cd_env_var(char *var_name, char *var_value, Shell *shell);
void cd(Shell *shell);
int compare_env_varname(const char *variable_name, const char *partial_name);
char *get_cd_env_variable(const char *variable_name, char **environment);

/* command_parser.c */
int parse_commandl(Shell *shell, char *user_input);
char **parse_commandl(char *user_input);
void create_nodes(Separator **s_head, CommandLine **c_head, char *user_input);
void next_commandl(Separator **set, CommandLine **com, Shell *shell);

/* bonus.c */
char *remove_non_print(char *user_input);
char *restore_non_print(char *user_input);
Separator *append_separator(Separator **head, char separator);
CommandLine *append_commandl(CommandLine **head, char *cmd);
int _strcmp(char string[], const char *delim);

/* errors_handling.c */
char *exit_error(Shell *shell);
char *env_error(Shell *shell);
int handle_errors(Shell *shell, int error);
int command_error(char *directory, Shell *shell);
char *not_found_error(Shell *shell);

/* cd_errors.c */
char *cd_error(Shell *shell);
char *cd_error_concat(Shell *shell, char *message, char *error, char *line);
char *path_error(Shell *shell);

/* builtins.c */
int change_directory(Shell *shell);
void previous_dir(Shell *shell);
void home_dir(Shell *shell);
int (*get_builtin(char *command))(Shell *);
int shell_exit(Shell *shell);

#endif

