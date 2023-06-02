#include "main.h"
/**
 * executeCommand - executes a command
 * @cmd: command to execute
 * @args: arguments passed
 * Return: Always 0.
 */
int executeCommand(char *cmd, char **args)
{
	int last_exit_status = 0;
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		last_exit_status = WEXITSTATUS(status);
	}
	return (last_exit_status);
}
