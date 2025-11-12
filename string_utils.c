#include "shell.h"

/**
 * _strlen - calculate length of a string
 * @s: string
 * Return: length
 */
int _strlen(const char *s)
{
    int i = 0;

    if (s == NULL)
        return (0);

    while (s[i])
        i++;

    return (i);
}

/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 if equal, positive or negative if different
 */
int _strcmp(const char *s1, const char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return (1);

    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }

    return (s1[i] - s2[i]);
}

