#include "timings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void result()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day2.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    size_t limit_red = 12;
    size_t limit_green = 13;
    size_t limit_blue = 14;

    size_t game_number = 0;

    size_t total1 = 0;
    size_t total2 = 0;

    while ((read = getline(&line, &length, fp)) != -1)
    {
        game_number++;
        size_t max_green = 0;
        size_t max_red = 0;
        size_t max_blue = 0;

        const char *delims = ":; ,";
        char *token;
        char *prev_token = "-1";

        token = strtok(line, delims);

        while (token)
        {
            if (*prev_token >= '0' && *prev_token <= '9')
            {
                if (strcmp(token, "blue") == 0 || strcmp(token, "blue\n") == 0)
                {
                    if (max_blue < atoi(prev_token))
                    {
                        max_blue = atoi(prev_token);
                    }
                }
                else if (strcmp(token, "red") == 0 || strcmp(token, "red\n") == 0)
                {
                    if (max_red < atoi(prev_token))
                    {
                        max_red = atoi(prev_token);
                    }
                }
                else if (strcmp(token, "green") == 0 || strcmp(token, "green\n") == 0)
                {
                    if (max_green < atoi(prev_token))
                    {
                        max_green = atoi(prev_token);
                    }
                }
            }

            prev_token = token;
            token = strtok(NULL, delims);
        }

        if (limit_red >= max_red && limit_blue >= max_blue && limit_green >= max_green)
        {
            total1 += game_number;
        }

        total2 += max_green * max_blue * max_red;
    }

    printf("Total part 1 is %zu\n", total1);
    printf("Total part 2 is %zu\n", total2);
}

int main()
{
    printf("Day 2 ran in %f seconds\n", get_performance(&result));
    exit(0);
}
