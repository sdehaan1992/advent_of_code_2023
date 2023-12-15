#include "timings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODES 770

typedef struct Node
{
    char name[4];
    struct Node *left;
    struct Node *right;
} Node;

size_t lcm(size_t a, size_t b);
size_t gcd(size_t a, size_t b);

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day8.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    Node nodes[NODES];
    getline(&line, &length, fp);
    char instruction_set[strlen(line) + 1];
    strcpy(instruction_set, line);
    getline(&line, &length, fp);

    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = "=, ()";
        char *token = strtok(line, delims);
        strcpy(nodes[linenum].name, token);
        nodes[linenum].left = NULL;
        nodes[linenum].right = NULL;
        linenum++;
    }

    rewind(fp);
    line = NULL;

    getline(&line, &length, fp);
    getline(&line, &length, fp);

    linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = "=, ()";
        char *token = strtok(line, delims);
        token = strtok(NULL, delims);

        Node *node = &nodes[linenum];
        for (int i = 0; i < NODES; i++)
        {
            if (i != linenum)
            {
                if (strcmp(token, nodes[i].name) == 0)
                {
                    node->left = &nodes[i];
                    break;
                }
            }
        }

        token = strtok(NULL, delims);
        for (int i = 0; i < NODES; i++)
        {
            if (i != linenum)
            {
                if (strcmp(token, nodes[i].name) == 0)
                {
                    node->right = &nodes[i];
                    break;
                }
            }
        }
        linenum++;
    }

    Node *current_pos = NULL;
    for (int i = 0; i < NODES; i++)
    {
        if (strcmp(nodes[i].name, "AAA") == 0)
        {
            current_pos = &nodes[i];
            break;
        }
    }

    int steps = 0;
    int instruction_count = 0;
    while (strcmp(current_pos->name, "ZZZ") != 0)
    {
        char instruction = instruction_set[instruction_count];

        switch (instruction)
        {
        case 'R':
            current_pos = current_pos->right;
            break;
        case 'L':
            current_pos = current_pos->left;
        }

        if (instruction_count == strlen(instruction_set) - 2)
        {
            instruction_count = -1;
        }
        steps++;
        instruction_count++;
    }

    printf("Total Part 1 is %i\n", steps);
}

void part2()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day8.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    Node nodes[NODES];
    getline(&line, &length, fp);
    char instruction_set[strlen(line) + 1];
    strcpy(instruction_set, line);
    getline(&line, &length, fp);
    int start_points = 0;

    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = "=, ()";
        char *token = strtok(line, delims);
        strcpy(nodes[linenum].name, token);
        nodes[linenum].left = NULL;
        nodes[linenum].right = NULL;

        if (token[2] == 'A')
        {
            start_points++;
        }

        linenum++;
    }

    rewind(fp);
    line = NULL;

    getline(&line, &length, fp);
    getline(&line, &length, fp);

    linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = "=, ()";
        char *token = strtok(line, delims);
        token = strtok(NULL, delims);

        Node *node = &nodes[linenum];
        for (int i = 0; i < NODES; i++)
        {
            if (i != linenum)
            {
                if (strcmp(token, nodes[i].name) == 0)
                {
                    node->left = &nodes[i];
                    break;
                }
            }
        }

        token = strtok(NULL, delims);
        for (int i = 0; i < NODES; i++)
        {
            if (i != linenum)
            {
                if (strcmp(token, nodes[i].name) == 0)
                {
                    node->right = &nodes[i];
                    break;
                }
            }
        }
        linenum++;
    }

    Node *current_positions[start_points];
    int pos_idx = 0;

    for (int i = 0; i < NODES; i++)
    {
        if (nodes[i].name[2] == 'A')
        {
            current_positions[pos_idx] = &nodes[i];
            pos_idx++;
        }
    }

    int steps = 0;
    int instruction_count = 0;
    _Bool finished = 0;

    int results[start_points];

    for (int i = 0; i < start_points; i++)
    {
        instruction_count = 0;
        steps = 0;
        Node *current_pos = current_positions[i];
        while (current_pos->name[2] != 'Z')
        {
            char instruction = instruction_set[instruction_count];

            switch (instruction)
            {
            case 'R':
                current_pos = current_pos->right;
                break;
            case 'L':
                current_pos = current_pos->left;
            }

            if (instruction_count == strlen(instruction_set) - 2)
            {
                instruction_count = -1;
            }
            steps++;
            instruction_count++;
        }
        results[i] = steps;
    }

    size_t current = 1;
    for (int i = 0; i < start_points; i++)
    {
        current = lcm(current, results[i]);
    }

    fclose(fp);
    free(line);
    printf("Total Part 2 is %zu\n", current);
}

size_t lcm(size_t a, size_t b)
{
    if (a > b)
    {
        return b * (a / gcd(a, b));
    }
    if (b > a)
    {
        return a * (b / gcd(b, a));
    }
    return a;
}

size_t gcd(size_t a, size_t b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int main()
{
    // printf("Part 1 ran for %f seconds\n", get_performance(&part1));
    printf("Part 2 ran for %f seconds\n", get_performance(&part2));
    exit(0);
}
