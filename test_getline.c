#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        write(1, "$ ", 2);
        nread = _getline(&line, &len);
        if (nread == -1)
        {
            write(1, "\n", 1);
            break;
        }
        write(1, "You typed: ", 11);
        write(1, line, nread);
    }

    free(line);
    return 0;
}
