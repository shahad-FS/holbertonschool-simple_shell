#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

ssize_t _getline(char **lineptr, size_t *n)
{
    static char buf[BUFFER_SIZE];
    static ssize_t buf_pos = 0;
    static ssize_t buf_len = 0;
    ssize_t total_read = 0;
    char *dst;
    size_t dst_size;

    if (!lineptr || !n)
    {
        errno = EINVAL;
        return -1;
    }

    if (*lineptr == NULL || *n == 0)
    {
        *n = 128;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return -1;
    }

    dst = *lineptr;
    dst_size = *n;

    while (1)
    {
        if (buf_pos >= buf_len)
        {
            buf_len = read(STDIN_FILENO, buf, BUFFER_SIZE);
            buf_pos = 0;

            if (buf_len <= 0)
                return (total_read > 0) ? total_read : -1;
        }

        while (buf_pos < buf_len)
        {
            char c = buf[buf_pos++];
            if ((size_t)(total_read + 1) >= dst_size)
            {
                dst_size *= 2;
                dst = realloc(dst, dst_size);
                if (!dst)
                    return -1;
                *lineptr = dst;
                *n = dst_size;
            }

            dst[total_read++] = c;
            if (c == '\n')
            {
                dst[total_read] = '\0';
                return total_read;
            }
        }
    }
}
