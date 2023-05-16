/*char *my_getline(void) {
    static char buffer[BUFFER_SIZE];
    static int position = 0;
    static ssize_t length = 0;

    char *line = NULL;
    size_t line_size = 0;

    while (1) {
        // Check if buffer is empty
        if (position >= length) {
            // Read more data into buffer
            length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            position = 0;
            if (length == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            } else if (length == 0) {
                // End of file reached
                break;
            }
        }

        // Search for newline character in buffer
        while (position < length && buffer[position] != '\n') {
            // Append character to line
            if (line_size == 0 || line[line_size - 1] != '\0') {
                line_size++;
                line = realloc(line, line_size);
                if (!line) {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
            }
            line[line_size - 1] = buffer[position];
            position++;
        }

        // Check if newline character was found
        if (position < length && buffer[position] == '\n') {
            position++;
            break;
        }
    }

    // Add null terminator to line
    if (line && line_size > 0 && line[line_size - 1] != '\0') {
        line_size++;
        line = realloc(line, line_size);
        if (!line) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        line[line_size - 1] = '\0';
    }

    return line;
}*/
