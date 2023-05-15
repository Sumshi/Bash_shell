/*#include "main.h"
int check_command_existence(const char *command) {
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");
	char command_path[BUFFER_SIZE];

	while (dir != NULL) {
		snprintf(command_path, BUFFER_SIZE, "%s/%s", dir, command);

		if (access(command_path, F_OK) == 0) {
			return 1; // Command exists
		}

		dir = strtok(NULL, ":");
	}

	return 0; // Command does not exist
}*/
