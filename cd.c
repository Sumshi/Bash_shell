#include "main.h"
void execute_cd(char *command)
{
	char cwd[BUFFER_SIZE];/*stores current working directory*/
	char *arg = strtok(command, " ");
	arg = strtok(NULL, " ");  // Get the argument after "cd"
	if (arg == NULL)
	{
		arg = getenv("HOME");  // If no argument, use the value of HOME environment variable
	}
	if (chdir(arg) == -1)
	{
		perror("chdir error");
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			/*printf("%s\n", cwd);*/
		} else {
			perror("getcwd error");
		}
	}
}
