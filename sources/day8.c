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
    char instruction_set[strlen(line)];
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
}

int main()
{
    part1();
    part2();
    exit(0);
}
