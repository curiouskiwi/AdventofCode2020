// Advent of Code - Day 19
// @curiouskiwi @gary_anderson
// 19 Dec 2020

#include <stdio.h>
#include <string.h>

int checkrule(char *m, int rulenum, int *offset);
int checkrule0(char *m);

typedef struct rule
{
    int one;
    int two;
    int three;
    int four;
}
rule;

rule rules[135];


int main(void)
{
    FILE *f = fopen("data.txt","r");
    if (!f)
    {
        printf("unable to open file\n");
        return -1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), f))
    {
        if (buffer[0] == '\n')
            break;

        int rulenum, one, two, three, four;
        one = two = three = four = -1;
        int r = sscanf(buffer, "%d:%d %d", &rulenum, &one, &two);
        if (r == 2 || r == 3)
        {
            char *left = strchr(buffer, '|');
            if (left)
                sscanf(left, "|%d %d\n", &three, &four);
        }

        if (r == 1)
        {
            char s;
            sscanf(buffer, "%d: \"%c\"", &rulenum, &s);
            one = -s;
        }

        rules[rulenum] = (rule){one, two, three, four};
    }

    // read in each message
    int part1total = 0, part2total = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        int offset = 0;

        // part 1
        if (checkrule(buffer, 0, &offset) && buffer[offset] == '\n')
            part1total++;

        // part 2
        if (checkrule0(buffer))
            part2total++;
    }

    printf("Part 1: %i\n", part1total);
    printf("Part 2; %i\n", part2total);

}

// special case for rule 0 which calls 8 & 11 and repeating 42s & 31s
// 0: 8 11
// 8: 42 | 42 8
//11: 42 31 | 42 11 31
// as long as there is one more 42 than 31, it meets the rules

int checkrule0(char *m)
{
    int offset = 0, count42 = 0, count31 = 0;

    while (checkrule(m, 42, &offset))
        count42++;

    while (checkrule(m, 31, &offset))
        count31++;

    if ((count31 < 1) || (count42 < count31 + 1) || m[offset] != '\n')
        return 0;

    return 1;
}


int checkrule(char *m, int rulenum, int *offset)
{
    // printf("checking rule %i\n", rulenum);
    int trialoffset = *offset;
    if (rulenum == -1)
        return 1;

    if (rules[rulenum].one < 0)
    {
        // match character "a" or "b"
        if (m[*offset] == -rules[rulenum].one)
        {
            (*offset)++;
            return 1;
        }
        else
            return 0;
    }

    if (checkrule(m, rules[rulenum].one, &trialoffset) &&
        checkrule(m, rules[rulenum].two, &trialoffset))
    {
        *offset = trialoffset;
        return 1;
    }
    if (rules[rulenum].three != -1)
    {
        trialoffset = *offset;
        if (checkrule(m, rules[rulenum].three, &trialoffset) &&
            checkrule(m, rules[rulenum].four, &trialoffset))
        {
            *offset = trialoffset;
            return 1;
        }
    }

    return 0;
}
