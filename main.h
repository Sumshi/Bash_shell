#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#define BUFFER_SIZE 1024
#define MAX_ARGS 100
#define MAX_ALIASES 100
#define BUFSIZE 1024
#define FAIL (-1)
#define SUCCESS (1)
#define PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define PROMPT "$ "
/*alias*/
/**
 * struct AliasNode - Alias node
 * @aliasName: name
 * @aliasValue: value
 * @next: to the next node
 */
typedef struct AliasNode
{
	char *aliasName;
	char *aliasValue;
	struct AliasNode *next;
} AliasNode;


/**
 * struct shell_data - Global data structure
 * @line: the line input
 * @args: the arguments token
 * @error_msg: the global path
 * @cmd: the parsed command
 * @index: the command index
 * @oldpwd: the old path visited
 * @env: the environnment
 * Description: A structure contains all the variables needed to manage
 *		the program, memory and accessability
 */
typedef struct shell_data
{
	char *line;
	char **args;
	char *cmd;
	char *error_msg;
	char *oldpwd;
	unsigned long int index;
	char *env;
} main_t;

extern int last_exit_status;
/*functions*/
int space_check(char *buffer);
int _putchar(char c);
void exitShell(int exitStatus);
int isComment(const char *line);
char *handleVariables(char *input);
extern char **environ;
int clear(void);
void printPrompt(void);
void check_exit(char **args);
void parseInput(char *buffer, char **args);
char *getAbsolutePath(char *command);
int executeCommand(char *cmd, char **args);
void printEnv(void);
int changeDirectory(char *directory);
int mySetEnv(char *var, char *value);
int myUnsetEnv(char *var);
void set_env(char **args);
void unset_env(char **args);
char **tokenize(char *str, char *delimiter);
/*string functions*/
unsigned int _strlen(char *str);
char *_strcpy(char *dest, char *src);
char *_strtok(char *str, const char *delim);
unsigned int check_match(char c, const char *str);
char *_strcat(char *dest, const char *src);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strdup(char *strtodup);
size_t _strcspn(const char *str1, const char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);
int _atoi(char *str);
int int_to_string(char *str, int num);
void reverse_string(char *str, int length);
void write_string(char *dest, char *src, int len);
/*printf family functions*/
int _snprintf(char *str, size_t size, const char *format, ...);
int _sprintf(char *str, const char *format, ...);
/*dynamic memoery allocations funcs*/
void *my_realloc(void *ptr, unsigned int size, unsigned int newsize);
/* vsprintf functions*/
char *s_itoa(int num, char *str);
int write_integer(char **str, int num);
/*getline*/
char *mem_cpy(char *dest, char *src, unsigned int i);
char *mem_set(char *str, char bytes, unsigned int i);
int freedata(main_t *data);
void *array_build(void *a, int element, unsigned int len);
ssize_t my_getline(main_t *data);
#endif
