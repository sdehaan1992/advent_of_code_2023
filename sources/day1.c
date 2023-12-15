#include "timings.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    char first_char = '\0';
    char last_char = '\0';

    size_t total = 0;

    fp = fopen("input/day1.txt", "r");
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

    printf("Total for part 1 is %lu\n", total);
    free(line);
}

void part2()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    size_t first_char = 0;
    size_t last_char = 0;

    char digits[18][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                          "1",   "2",   "3",     "4",    "5",    "6",   "7",     "8",     "9"};

    size_t total = 0;

    fp = fopen("input/day1.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }
    size_t line_num = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        line_num++;
        size_t offset_first = -1;
        size_t offset_last = -1;
        for (size_t j = 0; j < 18; j++)
        {
            char *found = strstr(line, digits[j]);
            if (found)
            {
                if (offset_first == -1 || offset_first > (found - line))
                {
                    offset_first = found - line;
                    if (j < 9)
                    {
                        first_char = (j + 1) * 10;
                    }
                    else
                    {
                        first_char = (j - 8) * 10;
                    }
                }

                char *next = "a";
                while (next)
                {
                    next = strstr(++found, digits[j]);
                    if (next)
                    {
                        found = next;
                    }
                }

                if (offset_last == -1 || offset_last < (found - line))
                {
                    offset_last = found - line;
                    if (j < 9)
                    {
                        last_char = (j + 1);
                    }
                    else
                    {
                        last_char = (j - 8);
                    }
                }
            }
        }

        total += first_char + last_char;
        first_char = 0;
        last_char = 0;
    }

    printf("Total for part 2 is %lu\n", total);
    free(line);
}

int main()
{
    printf("Part 1 ran in %f seconds\n", get_performance(&part1));
    printf("Part 2 ran in %f seconds\n", get_performance(&part2));
    exit(0);
}
