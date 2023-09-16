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

extern char **env;

typedef struct shell shell_t;
typedef struct builtins builtins_t;
typedef struct separator separator_t;
typedef struct cline cline_t;

/**
* struct shell - Structure representing the shell.
* @av: Command line arguments.
* @args: Parsed command line arguments.
* @user_input: User's command input.
* @status: Status of the shell.
* @line_count: Line counter.
* @_env: Environment variables.
* @pid_str: Process ID of the shell as a string.
*/

struct shell
{
	char **av;
	char *args;
	char *user_input;
	int status;
	int line_count;
	char **_env;
	char *pid_str;
};

/**
* struct builtins - Structure for shell built-in commands.
* @name: The name of the built-in command.
* @function: Pointer to the function implementing the command.
*/

struct builtins
{
	char *name;
	int (*function)(shell_t *s);
};
/**
* struct cline - Structure for a single linked list of command lines.
* @line: A command line node.
* @next: Pointer to the next node.
* Description: Single linked list to store command lines.
*/
struct cline
{
	char *line;
	struct cline *next;
};

/**
* struct separator - Structure for a single linked list of separators.
* @symbol: The separator character (e.g., ';').
* @next: Pointer to the next node.
* Description: Single linked list to store separators.
*/
struct separator
{
	char symbol;
	struct separator *next;
};

/* scan.c */
char *read_input(int *eof);
ssize_t _getline(char **outp_buffer, size_t *outp_size, FILE *inp_stream);
void _getline2(char **buffer, size_t *s, char *s_buffer, size_t inpsize);

/* strings.c */
char *copy_string(char *dest, char *src);
char *concatenate_strings(char *dest, const char *src);
char *duplicate_string(const char *str);
int compare_strings(char *s1, char *s2);
char *tokenize_string(char string[], const char *delimiter);

/* converters.c */
int count_digits(const char *str);
int string_length(const char *str);
char *integer_to_string(int num);
int string_to_integer(char *str);
int is_digit(const char *character);

/* memory.c */
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int size);
void *reallocate_mem(void *ptr, unsigned int old, unsigned int nw);
void free_separator_list(Separator **head);
void free_cline_list(CommandLine **head);
char **reallocate_dp(char **old_dp, unsigned int old, unsigned int nw);

/* commands.c */
int find_execommand(Shell *shell);
int execute_command(Shell *shell);
int is_commandexe(Shell *shell);
char *find_command(char *command, char **env);
int is_dir_path(char *path, int *index);

/* environment.c */
char *get_env_var(const char *var_name, char **env);
int print_env_var(shell_t *sh);
int _setenv(shell_t *sh);
int _unsetenv(shell_t *sh);
char *create_env_var(char *var_name, char *var_value);

/* cd_environment.c */
int compare_env_varname(const char *variable_name, const char *partial_name);
void set_cd(char *var_name, char *var_value, shell_t *sh);
void cd(Shell *shell);
char *get_cd_env(const char *var_name, char **_env);

/* command_parser.c */
int parse_commandl(shell_t *sh, char *user_input);
char **toke_commandl(char *user_input);
void create_nodes(separator_t **s_head, cline_t **c_head, char *user_input);
void next_commandl(separator_t **set, cline_t **com, shell_t *sh);

/* utils.c */
char *rm_non_print(char *user_input);
char *rest_non_print(char *user_input);
separator_t *append_separator(separator_t **head, char sep);
CommandLine *append_commandl(CommandLine **head, char *cmd);
int compare_cs(char str[], const char *lim);

/* errors_handling.c */
char *exit_error(shell_t *sh);
char *env_error(shell_t *sh);
int handle_errors(shell_t *sh, int error);
int command_error(char *directory, shell_t *sh);
char *not_found_error(shell_t *sh);

/* cd_errors.c */
char *cd_error(shell_t *sh);
char *cd_error_concat(shell_t *sh, char *message, char *error, char *line);
char *path_error(shell_t *sh);

/* builtins.c */
int change_directory(shell_t *sh);
void previous_dir(shell_t *sh);
void home_dir(shell_t *sh);
int (*get_builtin(char *cmd))(shell_t *)
int shell_exit(shell_t *sh);

#endif

