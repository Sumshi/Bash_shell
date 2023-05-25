#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 100
#define MAX_ARGS 10

void parseInput(char *buffer, char **args) {
    int argCount = 0;
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        args[argCount++] = token;
        if (argCount >= MAX_ARGS) {
            break;
        }
        token = strtok(NULL, " ");
    }
    args[argCount] = NULL;
}
void executeCommand(char *cmd, char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execve(cmd, args, NULL);
        perror("execve error");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, &status, 0);
    }
}
char *getAbsolutePath(char *command) {
    if (command[0] == '/') {
        // Command contains absolute path
        return strdup(command);
    }

    char *pathDirectory[MAX_ARGS + 2]; // increase size by 1 for /bin and 1 for null terminator
    int numDirectory = 0;

    pathDirectory[numDirectory++] = "/bin"; // add /bin to search path

    char *pathEnvVar = getenv("PATH");
    char *token = strtok(pathEnvVar, ":");
    while (token != NULL) {
        pathDirectory[numDirectory++] = token;
        if (numDirectory >= MAX_ARGS + 1) { // increase size check accordingly
            break;
        }
        token = strtok(NULL, ":");
    }
    pathDirectory[numDirectory] = NULL;

    for (int i = 0; i < numDirectory; i++) {
        char tempCmd[BUFFER_SIZE];
        snprintf(tempCmd, BUFFER_SIZE, "%s/%s", pathDirectory[i], command);
        if (access(tempCmd, X_OK) == 0) {
            return strdup(tempCmd);
        }
    }

    return NULL;
}
void printEnv() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}
int changeDirectory(char *directory) {
    if (directory == NULL || strcmp(directory, "~") == 0) { // Handle no argument or ~
        directory = getenv("HOME");
    }

    if (strcmp(directory, "-") == 0) { // Handle -
        directory = getenv("OLDPWD");
        char *msg = "Changing to previous directory: ";
        write(STDOUT_FILENO, msg, strlen(msg));
        write(STDOUT_FILENO, directory, strlen(directory));
        write(STDOUT_FILENO, "\n", 1);
    }

    char cwd[BUFFER_SIZE];
    getcwd(cwd, BUFFER_SIZE); // Get current working directory

    if (chdir(directory) != 0) { // Change the directory
        perror("cd error");
        return -1;
    }

    char newCwd[BUFFER_SIZE];
    getcwd(newCwd, BUFFER_SIZE); // Get new current working directory

    setenv("OLDPWD", cwd, 1); // Set OLDPWD environment variable
    setenv("PWD", newCwd, 1); // Set PWD environment variable

    return 0;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    ssize_t length;

    while (1) {
        if (isatty(STDIN_FILENO) == 1)
            write(STDOUT_FILENO, "$ ", 2);

        length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (length == -1) {
            perror("Error from read");
            exit(EXIT_FAILURE);
        }
        if (length == 0) {
            break;
        }
        if (buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        char *args[MAX_ARGS + 1]; /* 1 for null terminator */
        
		parseInput(buffer, args);

		if (strcmp(args[0], "exit") == 0) { // Handle exit command
			int status = EXIT_SUCCESS;
			if (args[1] != NULL) { // If argument is provided
				status = atoi(args[1]); // Convert to integer
			}
			exit(status); // Exit the shell with given status
		} else if (strcmp(args[0], "env") == 0) { // Handle env command
			printEnv();
			continue;
		} else if (strcmp(args[0], "cd") == 0) { // Handle cd command
			if (changeDirectory(args[1]) != 0) {
				continue;
			}
			continue;
		}

		char *cmd = getAbsolutePath(args[0]);
		
		if (cmd == NULL) {
			printf("%s: command not found\n", args[0]);
			continue;
		}

		executeCommand(cmd, args);

		free(cmd);
    }

    return 0;
}
