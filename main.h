#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define UNUSED(x) (void)(x)

extern char **environ;

typedef struct builtins mybuiltins;
typedef struct shell myshell;
typedef struct cline mycline;
typedef struct separator myseparator;

/**
* struct builtins - Structure for shell built-in commands.
* @name: The name of the built-in command.
* @function: Pointer to the function implementing the command.
*/

struct builtins
{
	char *name;
	int (*function)(myshell *s);
};

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
	char **args;
	char *user_input;
	int status;
	int line_count;
	char **_env;
	char *pid_str;
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

/* strings.c */
char *copy_string(char *dest, char *src);
char *concatenate_strings(char *dest, const char *src);
char *duplicate_string(const char *str);
int compare_strings(char *s1, char *s2);
char *tokenize_string(char string[], const char *delimiter);

/* converters.c */
int count_digits(int num);
int string_length(const char *str);
char *integer_to_string(int num);
int string_to_integer(char *str);
int is_digit(const char *character);

/* scan.c */
char *read_input(int *eof);
ssize_t _getline(char **outp_buffer, size_t *outp_size, FILE *inp_stream);
void _getline2(char **buffer, size_t *s, char *s_buffer, size_t inpsize);

/* commands.c */
int find_execommand(myshell *sh);
int execute_command(myshell *sh);
int is_exe(myshell *sh);
char *find_command(char *command, char **_env);
int is_dir_path(char *path, int *index);

/* command_parser.c */
int parse_commandl(myshell *sh, char *user_input);
char **toke_commandl(char *user_input);
void create_nodes(myseparator **s_head, mycline **c_head, char *user_input);
void next_commandl(myseparator **set, mycline **com, myshell *sh);

/* memory.c */
void copy_memory(void *dest_ptr, const void *src_ptr, unsigned int size);
void *reallocate_mem(void *ptr, unsigned int old, unsigned int nw);
void free_separator_list(myseparator **start);
void free_cline_list(mycline **start);
char **reallocate_dp(char **old_dp, unsigned int old, unsigned int nw);

/* environment.c */
char *get_env_var(const char *var_name, char **_env);
int print_env_var(myshell *sh);
int _setenv(myshell *sh);
int _unsetenv(myshell *sh);
char *create_env_var(char *var_name, char *var_value);

/* cd_environment.c */
int compare_env_varname(const char *variable_name, const char *partial_name);
void set_cd(char *var_name, char *var_value, myshell *sh);
void cd(myshell *sh);
char *get_cd_env(const char *var_name, char **_env);

/* utils.c */
char *rm_non_print(char *user_input);
char *rest_non_print(char *user_input);
myseparator *append_separator(myseparator **head, char sep);
mycline *append_commandl(mycline **head, char *cl);
int compare_cs(char str[], const char *lim);

/* errors_handling.c */
char *exit_error(myshell *sh);
char *env_error(myshell *sh);
int handle_errors(myshell *sh, int error);
int command_error(char *ddir, myshell *sh);
char *not_found_error(myshell *sh);

/* cd_errors.c */
char *cd_error(myshell *sh);
char *cd_error_concat(myshell *sh, char *message, char *error, char *line);
char *path_error(myshell *sh);

/* builtins.c */
int change_directory(myshell *sh);
void previous_dir(myshell *sh);
void home_dir(myshell *sh);
int (*builtins(char *command))(myshell *);
int shell_exit(myshell *sh);

#endif

