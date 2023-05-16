#include "main.h"
/*void print_environment() {
  extern char **environ; // The environment variable
  char **env = environ;

  while (*env)
  {
  printf ("%s\n", *env);
  env++;
  }
  }*/
void print_environment()
{
	extern char **environ;
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
