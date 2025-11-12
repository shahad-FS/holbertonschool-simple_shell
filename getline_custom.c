#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * _getline - Custom implementation of getline()
 * Reads a line from standard input using read() system call
 * @lineptr: Pointer to the buffer that will store the line
 *
 * Return: Number of characters read (excluding null terminator),
 * or -1 on failure or EOF.
 */
ssize_t _getline(char **lineptr)
{
    static char buffer[BUFFER_SIZE];
    static ssize_t buf_pos = 0;
    static ssize_t buf_size = 0;
    ssize_t i = 0;
    char *line = NULL;
    char c;

    if (!lineptr)
        return -1;

    line = malloc(BUFFER_SIZE);
    if (!line)
        return -1;

    while (1)
    {
        /* If buffer is empty, read a new chunk from stdin */
        if (buf_pos >= buf_size)
        {
            buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            buf_pos = 0;

            if (buf_size <= 0)
            {
                free(line);
                return -1; /* EOF or read error */
            }
        }

        /* Get the next character from the buffer */
        c = buffer[buf_pos++];

        /* Stop reading at newline or end of input */
        if (c == '\n' || c == '\0')
        {
            line[i] = '\0';
            *lineptr = line;
            return i;
        }

        line[i++] = c;

        /* If line is getting too big, reallocate more memory */
        if (i >= BUFFER_SIZE - 1)
        {
            char *new_line = realloc(line, i + BUFFER_SIZE);
            if (!new_line)
            {
                free(line);
                return -1;
            }
            line = new_line;
        }
    }
}
