#include "shell.h"
/**
 * process_file - reads a file and executes each line as a command
 * @filename: path to the file
 * @progname: shell name (for error messages)
 */
void process_file(char *filename, char *progname)
{
    int fd;
    ssize_t n;
    char buf[1024];
    char line[1024];
    int i, j;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        write(2, progname, strlen(progname));
        write(2, ": 0: Can't open ", 16);
        write(2, filename, strlen(filename));
        write(2, "\n", 1);
        exit(127);
    }

    j = 0;
    while ((n = read(fd, buf, sizeof(buf))) > 0)
    {
        for (i = 0; i < n; i++)
        {
            if (buf[i] == '\n')
            {
                line[j] = '\0';
                if (j > 0)
                    execute_command(line, progname);
                j = 0;
            }
            else if (j < 1023)
            {
                line[j++] = buf[i];
            }
        }
    }
    if (j > 0)
    {
        line[j] = '\0';
        execute_command(line, progname);
    }

    close(fd);
}
