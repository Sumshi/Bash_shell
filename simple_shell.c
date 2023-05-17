#include "main.h"
void execute_command(char *command)
{
	char buffer[BUFFER_SIZE], command_path[BUFFER_SIZE];
	pid_t pid;
	int status, index, j;
	char *path[] = { "/bin/", "/usr/bin/", NULL };
	char *args[BUFFER_SIZE];
	int arg_index = 0;
	int input_fd = STDIN_FILENO, output_fd = STDOUT_FILENO;
	int i = 0;
	char **input_args, **output_args;
	_strcpy(buffer, command);
	pid = fork();
	if (pid == -1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{ /* child process */
		args[arg_index++] = _strtok(buffer, " ");
		while (args[arg_index - 1] != NULL) {
			args[arg_index++] = _strtok(NULL, " ");
		}
		for (index = 0; args[index] != NULL; index++)
		{
			if (args[index][0] == '<')
			{
				input_args = &args[index + 1];
				handle_input_redirection(input_args);
				for (j = index; args[j] != NULL; j++)
				{
					args[j] = args[j + 2];
				}
				arg_index -= 2;
				index--;
			}
			else if (args[index][0] == '>')
			{
				output_args = &args[index + 1];
				handle_output_redirection(output_args);
				for (j = index; args[j] != NULL; j++)
				{
					args[j] = args[j + 2];
				}
				arg_index -= 2;
				index--;
			}
		}
		while (path[i] != NULL)
		{
			_strcpy(command_path, path[i]);
			_strcat(command_path, args[0]);
			if (access(command_path, X_OK) == 0)
				{
					break;
				}
			i++;
		}
		if (path[i] == NULL)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(98);
		}
		if (input_fd != STDIN_FILENO) {
			if (dup2(input_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			if (dup2(output_fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 error");
				exit(EXIT_FAILURE);
			}
			close(output_fd);
		}
		if (execve(command_path, args, NULL) == -1)
		{
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{ /* parent process */
		waitpid(pid, &status, 0);
	}
}
