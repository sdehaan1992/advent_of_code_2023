#include "timings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HANDS 1000

typedef enum HandType
{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_KIND,
    FULL_HOUSE,
    FOUR_OF_KIND,
    FIVE_OF_KIND
} HandType;

typedef enum CardType
{
    JOKER,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} CardType;

typedef struct LookupTable
{
    char letter;
    CardType card_type;
} LookupTable;

typedef struct Hand
{
    int bid;
    int card_values[5];
    HandType hand_type;
} Hand;

const LookupTable CardMap[] = {{'2', TWO},   {'3', THREE}, {'4', FOUR}, {'5', FIVE}, {'6', SIX},
                               {'7', SEVEN}, {'8', EIGHT}, {'9', NINE}, {'T', TEN},  {'J', JACK},
                               {'Q', QUEEN}, {'K', KING},  {'A', ACE}};

const LookupTable CardMapPart2[] = {{'2', TWO},   {'3', THREE}, {'4', FOUR}, {'5', FIVE}, {'6', SIX},
                                    {'7', SEVEN}, {'8', EIGHT}, {'9', NINE}, {'T', TEN},  {'J', JOKER},
                                    {'Q', QUEEN}, {'K', KING},  {'A', ACE}};
CardType get_card(const char *card)
{
    for (int i = 0; i < 13; i++)
    {
        if (*card == CardMap[i].letter)
        {
            return CardMap[i].card_type;
        }
    }

    return -1;
}

CardType get_card_part2(const char *card)
{
    for (int i = 0; i < 13; i++)
    {
        if (*card == CardMapPart2[i].letter)
        {
            return CardMapPart2[i].card_type;
        }
    }

    return -1;
}

int hand_comparator(const void *hand1, const void *hand2)
{
    Hand hand = *(Hand *)hand1;
    Hand otherHand = *(Hand *)hand2;

    int result = hand.hand_type - otherHand.hand_type;

    if (result != 0)
    {
        return result;
    }

    int card_num = 0;
    do
    {
        result = hand.card_values[card_num] - otherHand.card_values[card_num];
        card_num++;
    } while (result == 0 && card_num < 5);

    return result;
}

int card_comparator(const void *card1, const void *card2)
{
    int object1 = *(int *)card1;
    int object2 = *(int *)card2;
    return object2 - object1;
}

void part1()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day7.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    Hand hands[HANDS];

    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = " ";
        char *token = strtok(line, delims);

        int idx = 0;
        while (*token != '\0')
        {
            hands[linenum].card_values[idx] = get_card(token);
            idx++;
            token++;
        }

        int count[] = {1, 1, 1, 1, 1};
        for (int i = 0; i < 5; i++)
        {
            for (int j = i + 1; j < 5; j++)
            {
                if (hands[linenum].card_values[i] == hands[linenum].card_values[j])
                {
                    count[i]++;
                    count[j]++;
                }
            }
        }

        int highest = 0;
        int twos = 0;
        for (int i = 0; i < 5; i++)
        {
            if (count[i] > highest)
            {
                highest = count[i];
            }
            if (count[i] == 2)
            {
                twos++;
            }
        }

        switch (highest)
        {
        case 5:
            hands[linenum].hand_type = FIVE_OF_KIND;
            break;
        case 4:
            hands[linenum].hand_type = FOUR_OF_KIND;
            break;
        case 3:
            if (twos == 2)
            {
                hands[linenum].hand_type = FULL_HOUSE;
            }
            else
            {
                hands[linenum].hand_type = THREE_OF_KIND;
            }
            break;
        case 2:
            if (twos == 2)
            {
                hands[linenum].hand_type = ONE_PAIR;
            }
            else
            {
                hands[linenum].hand_type = TWO_PAIR;
            }
            break;
        default:
            hands[linenum].hand_type = HIGH_CARD;
        }

        token = strtok(NULL, delims);
        hands[linenum].bid = strtol(token, &token, 10);
        linenum++;
    }

    qsort(&hands, HANDS, sizeof(Hand), &hand_comparator);

    size_t total = 0;
    for (int i = 0; i < HANDS; i++)
    {
        total += hands[i].bid * (i + 1);
    }

    printf("Total Part 1 is %zu\n", total);
    free(line);
}

void part2()
{
    FILE *fp;
    char *line = NULL;
    size_t length = 0;
    ssize_t read;

    fp = fopen("input/day7.txt", "r");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(-1);
    }

    Hand hands[HANDS];

    int linenum = 0;
    while ((read = getline(&line, &length, fp)) != -1)
    {
        const char *delims = " ";
        char *token = strtok(line, delims);

        int idx = 0;
        int jokers = 0;
        while (*token != '\0')
        {
            hands[linenum].card_values[idx] = get_card_part2(token);
            if (hands[linenum].card_values[idx] == 0)
            {
                jokers++;
            }
            idx++;
            token++;
        }

        int count[] = {1, 1, 1, 1, 1};
        for (int i = 0; i < 5; i++)
        {
            for (int j = i + 1; j < 5; j++)
            {
                if (hands[linenum].card_values[i] != 0 &&
                    hands[linenum].card_values[i] == hands[linenum].card_values[j])
                {
                    count[i]++;
                    count[j]++;
                }
            }
        }

        int highest = 0;
        int twos = 0;
        for (int i = 0; i < 5; i++)
        {
            if (count[i] > highest)
            {
                highest = count[i];
            }
            if (count[i] == 2)
            {
                twos++;
            }
        }

        switch (highest + jokers)
        {
        case 6:
        case 5:
            hands[linenum].hand_type = FIVE_OF_KIND;
            break;
        case 4:
            hands[linenum].hand_type = FOUR_OF_KIND;
            break;
        case 3:
            if ((twos == 2 && jokers == 0) || (twos > 2 && jokers > 0))
            {
                hands[linenum].hand_type = FULL_HOUSE;
            }
            else
            {
                hands[linenum].hand_type = THREE_OF_KIND;
            }
            break;
        case 2:
            if (twos <= 2)
            {
                hands[linenum].hand_type = ONE_PAIR;
            }
            else
            {
                hands[linenum].hand_type = TWO_PAIR;
            }
            break;
        default:
            hands[linenum].hand_type = HIGH_CARD;
        }

        token = strtok(NULL, delims);
        hands[linenum].bid = strtol(token, &token, 10);
        linenum++;
    }

    qsort(&hands, HANDS, sizeof(Hand), &hand_comparator);

    size_t total = 0;
    for (int i = 0; i < HANDS; i++)
    {
        total += hands[i].bid * (i + 1);
    }

    printf("Total Part 2 is %zu\n", total);
    free(line);
}

int main()
{
    printf("Part 1 ran in %f seconds\n", get_performance(&part1));
    printf("Part 2 ran in %f seconds\n", get_performance(&part2));
    exit(0);
}
