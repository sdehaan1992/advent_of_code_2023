#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Line
{
    char *characters;
} Line;

int main()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    char first_char = '\0';
    char last_char = '\0';

    size_t total = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    while ((read = getline(&line, &length, fp)) != -1)
    {
        for (size_t i = 0; i < read - 1; i++)
        {
            if (first_char == '\0' && (line[i] > 47 && line[i] < 58))
            {
                first_char = line[i];
            }
            else if (line[i] > 47 && line[i] < 58)
            {
                last_char = line[i];
            }
        }

        if (last_char == '\0')
        {
            last_char = first_char;
        }

        size_t first = (first_char - '0') * 10;
        size_t last = last_char - '0';

        total += first + last;
        first_char = '\0';
        last_char = '\0';
    }

    printf("Total is %lu\n", total);
    free(line);
    exit(0);
}
