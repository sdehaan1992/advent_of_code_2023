#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
    size_t x;
    size_t y;
} Point;

typedef struct PartNumber
{
    Point start;
    Point end;
    size_t number;
} PartNumber;

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    Point *symbols = (Point *)malloc(6 * sizeof(Point));
    PartNumber *parts = (PartNumber *)malloc(10 * sizeof(PartNumber));

    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    size_t linenum = 0;
    size_t num_symbols = 0;
    size_t num_parts = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        size_t colnum = 0;
        while (*line != '\n' && *line != '\0')
        {
            // printf("current char is %c\n", *line);
            if ((*line < '0' || *line > '9') && *line != '.')
            {
                symbols[num_symbols].x = colnum;
                symbols[num_symbols].y = linenum;
                printf("created new symbol at x: %zu, y: %zu\n", colnum, linenum);
                line++;
                colnum++;
            }
            else if (*line >= '0' && *line <= '9')
            {
                parts[num_parts].number = strtol(line, &line, 10);
                parts[num_parts].start.x = colnum;
                parts[num_parts].start.y = linenum;
                colnum += ceil(log10(parts[num_parts].number));
                printf("Stored %zu at x: %zu, y: %zu \n", parts[num_parts].number, parts[num_parts].start.x,
                       parts[num_parts].start.y);
            }
            else
            {
                line++;
                colnum++;
            }
        }
        linenum++;
    }

    free(symbols);
    free(parts);
}

void part2();

int main()
{
    part1();
    // part2();
    exit(0);
}
