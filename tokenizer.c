#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * tokenize_input - splits a line into tokens by space or tab
 * @line: input string
 *
 * Return: array of strings (NULL-terminated)
 */
char **tokenize_input(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(sizeof(char *) * bufsize);
    char *token;
    int start = 0, end = 0, len = 0;

    if (!tokens)
        return NULL;

    while (line[end] != '\0')
    {
        /* Skip leading spaces or tabs */
        while (line[start] == ' ' || line[start] == '\t')
            start++, end++;

        /* Move end until a space or end of string */
        while (line[end] != ' ' && line[end] != '\t' && line[end] != '\0')
            end++;

        len = end - start;
        if (len > 0)
        {
            token = malloc(len + 1);
            if (!token)
                return NULL;

            strncpy(token, line + start, len);
            token[len] = '\0';
            tokens[i++] = token;

            if (i >= bufsize)
            {
                bufsize += 64;
                tokens = realloc(tokens, sizeof(char *) * bufsize);
                if (!tokens)
                    return NULL;
            }
        }

        start = end;
    }

    tokens[i] = NULL;
    return tokens;
}

