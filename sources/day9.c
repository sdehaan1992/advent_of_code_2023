#include "timings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 200
#define NUMBERS 21

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day9.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    int histories[LINES][NUMBERS];

    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        char *scanner = line;
        int i = 0;
        while (*scanner != '\0' && *scanner != '\n')
        {
            histories[linenum][i] = strtol(scanner, &scanner, 10);
            i++;
        }
        linenum++;
    }

    int total = 0;
    for (int i = 0; i < LINES; i++)
    {
        int *data_rows[NUMBERS];

        for (int j = NUMBERS - 1; j >= 0; j--)
        {
            data_rows[NUMBERS - (j + 1)] = (int *)calloc(j + 2, sizeof(int));
        }

        memcpy(data_rows[0], histories[i], NUMBERS * sizeof(int));
        for (int j = 1; j < NUMBERS; j++)
        {
            for (int k = 0; k < (NUMBERS - j); k++)
            {
                data_rows[j][k] = data_rows[j - 1][k + 1] - data_rows[j - 1][k];
            }
        }

        data_rows[NUMBERS - 1][1] = 0;

        for (int j = NUMBERS - 2; j >= 0; j--)
        {
            data_rows[j][NUMBERS - j] = data_rows[j][NUMBERS - j - 1] + data_rows[j + 1][NUMBERS - j - 1];
        }

        total += data_rows[0][NUMBERS];
        for (int i = 0; i < NUMBERS; i++)
        {
            free(data_rows[i]);
        }
    }

    printf("Total Part 1 is %i\n", total);

    fclose(fp);
    free(line);
}

void part2()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day9.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    int histories[LINES][NUMBERS];

    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        char *scanner = line;
        int i = 0;
        while (*scanner != '\0' && *scanner != '\n')
        {
            histories[linenum][i] = strtol(scanner, &scanner, 10);
            i++;
        }
        linenum++;
    }

    int total = 0;
    for (int i = 0; i < LINES; i++)
    {
        int *data_rows[NUMBERS];

        for (int j = NUMBERS - 1; j >= 0; j--)
        {
            data_rows[NUMBERS - (j + 1)] = (int *)calloc(j + 2, sizeof(int));
        }

        memcpy(data_rows[0], histories[i], NUMBERS * sizeof(int));
        for (int j = 1; j < NUMBERS; j++)
        {
            for (int k = 0; k < (NUMBERS - j); k++)
            {
                data_rows[j][k] = data_rows[j - 1][k + 1] - data_rows[j - 1][k];
            }
        }

        data_rows[NUMBERS - 1][1] = 0;

        for (int j = NUMBERS - 2; j >= 0; j--)
        {
            // last = same row first - next row last
            data_rows[j][NUMBERS - j] = data_rows[j][0] - data_rows[j + 1][NUMBERS - j - 1];
        }

        total += data_rows[0][NUMBERS];
        for (int i = 0; i < NUMBERS; i++)
        {
            free(data_rows[i]);
        }
    }

    printf("Total Part 2 is %i\n", total);

    fclose(fp);
    free(line);
}

int main()
{
    printf("Part 1 ran for %f seconds\n", get_performance(&part1));
    printf("Part 2 ran for %f seconds\n", get_performance(&part2));
    exit(0);
}
