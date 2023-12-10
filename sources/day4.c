#include "timings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("../input/day4.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    int total = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = ":|";
        int winning_numbers[10];
        int card_numbers[25];

        // first token is card number, not important
        char *token = strtok(line, delims);

        // Winning numbers
        token = strtok(NULL, delims);
        int number = -1;
        int index = 0;
        while ((number = strtol(token, &token, 10)) != 0)
        {
            winning_numbers[index] = number;
            index++;
        }

        // Card numbers
        token = strtok(NULL, delims);
        number = -1;
        index = 0;
        while ((number = strtol(token, &token, 10)) != 0)
        {
            card_numbers[index] = number;
            index++;
        }

        int card_value = 0;
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (card_numbers[i] == winning_numbers[j])
                {
                    if (card_value == 0)
                    {
                        card_value = 1;
                    }
                    else
                    {
                        card_value *= 2;
                    }
                }
            }
        }
        total += card_value;
    }
    free(line);
    printf("Total for part 1 is %i\n", total);
}

void part2()
{
}

int main()
{
    printf("Part 1 ran in %f seconds\n", get_performance(&part1));
    part2();
    exit(0);
}
