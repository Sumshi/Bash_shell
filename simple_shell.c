#include "main.h"
int main() {
        char buffer[BUFFER_SIZE];
        ssize_t length;
        int clear_requested = 0;

        while (1) {
                if (isatty(STDIN_FILENO)) {
                        write(STDOUT_FILENO, "$ ", 2);
                }

                length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
                if (clear_requested) { // Clear the screen before executing the command
                        clear();
                        clear_requested = 0;
                }

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
                } else if (strcmp(args[0], "setenv") == 0) { // Handle setenv command
                        if (args[1] == NULL || args[2] == NULL) {
                                char msg[] = "Usage: setenv VARIABLE VALUE\n";
                                write(STDOUT_FILENO, msg, strlen(msg));
                                continue;
                        }
                        if (mySetEnv(args[1], args[2]) != 0) {
                                continue;
                        }
                } else if (strcmp(args[0], "unsetenv") == 0) { // Handle unsetenv command
                        if (args[1] == NULL) {
                                char msg[] = "Usage: unsetenv VARIABLE\n";
                                write(STDOUT_FILENO, msg, strlen(msg));
                                continue;
                        }
                        if (myUnsetEnv(args[1]) != 0) {
                                continue;
                        }
                } else if (strcmp(args[0], "clear") == 0) { // Handle clear command
                        clear_requested = 1;
                } else {
                        char *cmd = getAbsolutePath(args[0]);

                        if (cmd == NULL) {
                                char msg[] = ": command not found\n";
                                write(STDOUT_FILENO, args[0], strlen(args[0]));
                                write(STDOUT_FILENO, msg, strlen(msg));
                        } else {
                                executeCommand(cmd, args);
                        }

                        free(cmd);
                }

                continue; // Move the continue statement to the end of the loop body
        }

        return 0;
}

