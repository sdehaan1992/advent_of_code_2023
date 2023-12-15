#include "timings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CARDS 205
#define WINNING_NUMBERS 10
#define CARD_NUMBERS 25

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day4.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    int total = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = ":|";
        int winning_numbers[WINNING_NUMBERS];
        int card_numbers[CARD_NUMBERS];

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
        for (int i = 0; i < CARD_NUMBERS; i++)
        {
            for (int j = 0; j < WINNING_NUMBERS; j++)
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

    if (fclose(fp) != 0)
    {
        exit(1);
    }

    free(line);
    printf("Total for part 1 is %i\n", total);
}

void part2()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day4.txt", "r");
    if (fp == NULL)
    {
        exit(-1);
    }

    int cards[NUM_CARDS];
    for (int i = 0; i < NUM_CARDS; i++)
    {
        cards[i] = 1;
    }

    int total = 0;
    int card_index = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = ":|";
        int winning_numbers[WINNING_NUMBERS];
        int card_numbers[CARD_NUMBERS];

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

        int extra_copies = 0;
        for (int i = 0; i < CARD_NUMBERS; i++)
        {
            for (int j = 0; j < WINNING_NUMBERS; j++)
            {
                if (card_numbers[i] == winning_numbers[j])
                {
                    extra_copies++;
                }
            }
        }

        for (int i = 1; i <= extra_copies; i++)
        {
            cards[card_index + i] += cards[card_index];
        }
        card_index++;
    }

    for (int i = 0; i < NUM_CARDS; i++)
    {
        total += cards[i];
    }

    if (fclose(fp) != 0)
    {
        exit(1);
    }

    printf("Total part 2 is %i\n", total);
    free(line);
}

int main()
{
    printf("Part 1 ran in %f seconds\n", get_performance(&part1));
    printf("Part 2 ran in %f seconds\n", get_performance(&part2));
    exit(0);
}
