#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mapping
{
    size_t source_range_start;
    size_t dest_range_start;
    size_t range_length;
} Mapping;

typedef struct Map
{
    int num_mappings;
    Mapping *mappings;
} Map;

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("../input/day5.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    Map maps[7];

    // Get seeds from first line
    size_t seeds[20];
    getline(&line, &length, fp);
    const char *delims = ":";

    // seeds:
    char *token = strtok(line, delims);

    token = strtok(NULL, delims);

    int index = 0;
    while (*token != '\n')
    {
        seeds[index] = strtol(token, &token, 10);
        index++;
    }

    getline(&line, &length, fp);

    for (int i = 0; i < 7; i++)
    {
        Map *current_map = &maps[i];
        current_map->num_mappings = 1;
        current_map->mappings = (Mapping *)calloc(current_map->num_mappings, sizeof(Mapping));
        getline(&line, &length, fp);

        int read = 0;
        int mapping_idx = 0;
        while ((read = getline(&line, &length, fp)) != -1)
        {
            if (read == 1)
            {
                break;
            }
            if (mapping_idx == current_map->num_mappings)
            {
                current_map->num_mappings *= 2;
                current_map->mappings =
                    (Mapping *)realloc(current_map->mappings, current_map->num_mappings * sizeof(Mapping));
            }
            char *search = line;
            Mapping mapping;
            mapping.dest_range_start = strtol(search, &search, 10);
            mapping.source_range_start = strtol(search, &search, 10);
            mapping.range_length = strtol(search, &search, 10);
            current_map->mappings[mapping_idx] = mapping;
            mapping_idx++;
        }
    }

    size_t lowest_number = LONG_MAX;

    for (int i = 0; i < 20; i++)
    {
        size_t cur_seed = seeds[i];

        for (int j = 0; j < 7; j++)
        {
            Map cur_map = maps[j];
            for (int k = 0; k < cur_map.num_mappings; k++)
            {
                Mapping cur_mapping = cur_map.mappings[k];
                if (cur_mapping.source_range_start <= cur_seed &&
                    cur_mapping.source_range_start + cur_mapping.range_length >= cur_seed)
                {
                    cur_seed = cur_seed - cur_mapping.source_range_start + cur_mapping.dest_range_start;
                    break;
                }
            }
        }

        if (cur_seed < lowest_number)
        {
            lowest_number = cur_seed;
        }
    }

    if (fclose(fp) != 0)
    {
        exit(1);
    }

    printf("Result for Part 1 is %zu\n", lowest_number);
    free(line);
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
