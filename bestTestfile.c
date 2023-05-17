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

		if (strcmp(args[0], "exit") == 0) {
			break; // Exit the shell
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
