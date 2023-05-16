#include "main.h"
void execute_command(char *command)
{
	char buffer[BUFFER_SIZE], command_path[BUFFER_SIZE];
	pid_t pid;/*stores process id*/
	int status;/*stores status of child process*/
	char *path[] = { "/bin/", "/usr/bin/", NULL };/*path where commands are found*/
	char *args[BUFFER_SIZE];/*stores commands and its arguments*/
	int arg_index = 0;
	int input_fd = STDIN_FILENO, output_fd = STDOUT_FILENO;
	int index, j;
	int i = 0;
	_strcpy(buffer, command);/*copies command string to buffer*/
	pid = fork();/*creates a new process*/
	if (pid == -1)/*error occured during forking*/
	{
		perror("error");
		exit(98);
	}
	else if (pid == 0)
	{ /* child process */
		args[arg_index++] = _strtok(buffer, " "); /* tokenize the command */
		while (args[arg_index - 1] != NULL)
		{
			args[arg_index++] = _strtok(NULL, " ");
		}
		/*Check for input/output redirection symbols*/
		for (index = 0; args[index] != NULL; index++)
		{
			if (args[index][0] == '<') {
				input_fd = open(args[index+1], O_RDONLY);
				if (input_fd == -1)
				{
					perror("open error");
					exit(98);
				}
				for (j = index; args[j] != NULL; j++)
				{
					args[j] = args[j+2];
				}
				arg_index -= 2;
				index--;/*Adjust the loop counter since we removed two arguments*/
			}
			else if (args[index][0] == '>')
			{
				output_fd = open(args[index+1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
				if (output_fd == -1)
				{
					perror("open error");
					exit(98);
				}
				for (j = index; args[j] != NULL; j++)
				{
					args[j] = args[j+2];
				}
				arg_index -= 2;
				index--;/*Adjust the loop counter since we removed two arguments*/
			}
		}
		while (path[i] != NULL) {
			_strcpy(command_path, path[i]);
			_strcat(command_path, args[0]);
			if (access(command_path, X_OK) == 0)
			{ /* executable command found */
				break;
			}
			i++;
		}
		if (path[i] == NULL)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(98);
		}
		/*Redirect input/output*/
		if (input_fd != STDIN_FILENO)
		{/*duplicates the file to the stdin*/
			if (dup2(input_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 error");
				exit(98);
			}
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{/*duplicates the file to stdout*/
			if (dup2(output_fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 error");
				exit(98);
			}
			close(output_fd);
		}

		if (execve(command_path, args, NULL) == -1)
		{
			perror("execve error");
			exit(98);
		}
	}
	else
	{ /* parent process */
		waitpid(pid, &status, 0);
	}
}
