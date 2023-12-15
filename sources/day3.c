#include "timings.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct PartNumber
{
    Point start;
    size_t number;
} PartNumber;

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day3.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    int num_symbols = 0;
    int num_parts = 0;
    int char_count = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        char *temp = line;
        while (*temp != '\n' && *temp != '\0')
        {
            char_count++;
            if ((*temp < '0' || *temp > '9') && *temp != '.')
            {
                num_symbols++;
                temp++;
            }
            else if (*temp >= '0' && *temp <= '9')
            {
                long int value = strtol(temp, &temp, 10);
                num_parts++;
            }
            else
            {
                temp++;
            }
        }
    }

    rewind(fp);
    free(line);

    Point *symbols = (Point *)malloc(num_symbols * sizeof(Point));
    PartNumber *parts = (PartNumber *)malloc(num_parts * sizeof(PartNumber));

    line = NULL;
    size_t linenum = 0;
    num_symbols = 0;
    num_parts = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        size_t colnum = 0;
        char *temp = line;
        while (*temp != '\n' && *temp != '\0')
        {
            if ((*temp < '0' || *temp > '9') && *temp != '.')
            {
                symbols[num_symbols].x = colnum;
                symbols[num_symbols].y = linenum;
                temp++;
                colnum++;
                num_symbols++;
            }
            else if (*temp >= '0' && *temp <= '9')
            {
                parts[num_parts].number = strtol(temp, &temp, 10);
                parts[num_parts].start.x = colnum;
                parts[num_parts].start.y = linenum;

                colnum += floor(log10(parts[num_parts].number) + 1);

                num_parts++;
            }
            else
            {
                temp++;
                colnum++;
            }
        }
        linenum++;
    }

    free(line);
    if (fclose(fp) != 0)
    {
        exit(1);
    }

    size_t total = 0;
    for (int i = 0; i < num_parts; i++)
    {
        PartNumber part = parts[i];

        int num_adjacent_points = (floor(log10(part.number) + 1) + 2) * 3;

        for (int j = 0; j < num_adjacent_points; j++)
        {
            for (int x = part.start.x - 1; x <= part.start.x + (part.number < 10 ? 1 : floor(log10(part.number) + 1));
                 x++)
            {
                for (int y = part.start.y - 1; y <= part.start.y + 1; y++)
                {
                    for (int symbol = 0; symbol < num_symbols; symbol++)
                    {
                        if (symbols[symbol].x == x && symbols[symbol].y == y)
                        {
                            total += part.number;
                            goto next_part;
                        }
                    }
                }
            }
        }

    next_part:;
    }

    printf("Total part 1 is %zu\n", total);
    free(symbols);
    free(parts);
}

void part2()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day3.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    int num_gears = 0;
    int num_parts = 0;
    int char_count = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        char *temp = line;
        while (*temp != '\n' && *temp != '\0')
        {
            char_count++;
            if (*temp == '*')
            {
                num_gears++;
                temp++;
            }
            else if (*temp >= '0' && *temp <= '9')
            {
                long int value = strtol(temp, &temp, 10);
                num_parts++;
            }
            else
            {
                temp++;
            }
        }
    }

    rewind(fp);
    free(line);

    Point *gears = (Point *)malloc(num_gears * sizeof(Point));
    PartNumber *parts = (PartNumber *)malloc(num_parts * sizeof(PartNumber));

    line = NULL;
    size_t linenum = 0;
    num_gears = 0;
    num_parts = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        size_t colnum = 0;
        char *temp = line;
        while (*temp != '\n' && *temp != '\0')
        {
            if (*temp == '*')
            {
                gears[num_gears].x = colnum;
                gears[num_gears].y = linenum;
                temp++;
                colnum++;
                num_gears++;
            }
            else if (*temp >= '0' && *temp <= '9')
            {
                parts[num_parts].number = strtol(temp, &temp, 10);
                parts[num_parts].start.x = colnum;
                parts[num_parts].start.y = linenum;

                colnum += floor(log10(parts[num_parts].number) + 1);

                num_parts++;
            }
            else
            {
                temp++;
                colnum++;
            }
        }
        linenum++;
    }

    free(line);
    if (fclose(fp) != 0)
    {
        exit(1);
    }

    size_t total = 0;
    for (int i = 0; i < num_gears; i++)
    {
        Point gear = gears[i];
        int adjacent_parts[2] = {-1, -1};

        for (int j = 0; j < num_parts; j++)
        {
            PartNumber cur_part = parts[j];
            int start_x = cur_part.start.x;
            int end_x = start_x + floor(log10(cur_part.number));
            int start_y = cur_part.start.y;

            for (int y = gear.y - 1; y <= gear.y + 1; y++)
            {
                if (start_y == y && (start_x <= gear.x + 1 && end_x >= gear.x - 1))
                {
                    if (adjacent_parts[0] == -1)
                    {
                        adjacent_parts[0] = cur_part.number;
                        continue;
                    }
                    if (adjacent_parts[1] == -1)
                    {
                        adjacent_parts[1] = cur_part.number;
                        continue;
                    }
                    goto next_gear;
                }
            }
        }

        if (adjacent_parts[1] != -1)
        {
            total += (long)adjacent_parts[0] * adjacent_parts[1];
        }
    next_gear:;
    }

    printf("Total part 2 is %zu\n", total);
    free(gears);
    free(parts);
}

int main()
{
    printf("Part 1 ran in %f seconds\n", get_performance(&part1));
    printf("Part 2 ran in %f seconds\n", get_performance(&part2));
    exit(0);
}
