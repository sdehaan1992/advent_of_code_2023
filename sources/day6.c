#include "timings.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record
{
    int time;
    int distance;
} Record;

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day6.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    int times[4];
    int distances[4];

    int total = 1;
    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = ":";
        char *token = strtok(line, delims);
        token = strtok(NULL, delims);

        long number;
        int idx = 0;
        while ((number = strtol(token, &token, 10)) != 0L)
        {
            if (linenum == 0)
            {
                times[idx] = number;
            }
            else
            {
                distances[idx] = number;
            }
            idx++;
        }
        linenum++;
    }

    for (int time = 0; time < 4; time++)
    {
        int ways_to_beat_record = 0;
        for (int ms = 1; ms < times[time]; ms++)
        {
            int distance = (times[time] - ms) * ms;
            if (distance > distances[time])
            {
                ways_to_beat_record++;
            }
        }

        total *= ways_to_beat_record;
    }

    printf("Total for Part 1 is %i\n", total);
    if (fclose(fp) != 0)
    {
        exit(1);
    }
    free(line);
}

void part2()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day6.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    size_t time;
    size_t distance;

    int total = 1;
    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = ":";
        char *token = strtok(line, delims);
        token = strtok(NULL, delims);

        char *scanner = token;
        int numbers = 0;
        for (int i = 0; scanner[i] != '\0'; i++)
        {
            if (scanner[i] >= '0' && scanner[i] <= '9')
            {
                scanner[numbers] = scanner[i];
                numbers++;
            }
        }

        scanner[numbers] = '\0';
        if (linenum == 0)
        {
            time = strtol(scanner, &scanner, 10);
        }
        else
        {
            distance = strtol(scanner, &scanner, 10);
        }

        linenum++;
    }

    int ms_to_beat_record = 0;
    for (int ms = 1; ms < time; ms++)
    {
        size_t reached_distance = (time - ms) * ms;
        if (reached_distance > distance)
        {
            ms_to_beat_record = ms;
            break;
        }
    }

    printf("Total for Part 2 is %zu\n", time - ((long)2 * ms_to_beat_record) + 1);

    if (fclose(fp) != 0)
    {
        exit(1);
    }
    free(line);
}

int main()
{
    printf("Part 1 ran in %f seconds\n", get_performance(&part1));
    printf("Part 2 ran in %f seconds\n", get_performance(&part2));
    exit(0);
}
