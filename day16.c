// Advent of Code - Day 16
// @curiouskiwi - @gary_anderson
// 16 Dec 2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define FIELDS 20
void checkrows(int rows, int cols, int pos[rows][cols]);

typedef struct field
{
    char desc[50];
    int start[2];
    int end[2];
}
field;

field notes[FIELDS];


int main(void)
{
    FILE *f = fopen("data.txt", "r");

    // class: 1-3 or 5-7
    for (int i = 0; i < FIELDS; i++)
    {
        fscanf(f, "%[^:]: %d-%d or %d-%d\n",
            notes[i].desc, &notes[i].start[0],
            &notes[i].end[0], &notes[i].start[1], &notes[i].end[1]);

        //printf("%s %d-%d %d-%d\n", notes[i].desc, notes[i].start[0],
            //notes[i].end[0], notes[i].start[1], notes[i].end[1]);
    }
    char line[100];
    int ticket[FIELDS];
    fgets(line, sizeof(line), f);
    fgets(line, sizeof(line), f);
    // printf("parsing ... %s", line);
    char *nn = strtok(line, ",");
    ticket[0] = atoi(nn);
    int ctt = 1;
    while ((nn = strtok(NULL, ",")))
    {
        ticket[ctt] = atoi(nn);
        ctt++;
    }

    // consume the lines we don't need
    do
    {
        fgets(line, sizeof(line), f);
        // printf("skipping ... %s", line);
    }
    while (strstr(line, "nearby tickets:")==NULL);

    int badvalues = 0;
    int nums[FIELDS];

    // matrix of field positions
    int fieldposs[FIELDS][FIELDS];
    for (int i = 0; i < FIELDS; i++)
        for (int j = 0; j < FIELDS; j++)
            fieldposs[i][j] = 1;

    // read in each ticket
    while (fgets(line, sizeof(line), f))
    {
        // printf("parsing ... %s", line);
        char *n = strtok(line, ",");
        nums[0] = atoi(n);

        int ct = 1;
        while ((n = strtok(NULL, ",")))
        {
            nums[ct] = atoi(n);
            ct++;
        }

        int validticket = 1;
        for (int i = 0; i < ct; i++)
        {
            int validnum = 0;
            for (int k = 0; k < FIELDS; k++)
            {
                // check if num is within a range for any of the fields
                if ((nums[i] >= notes[k].start[0] && nums[i] <= notes[k].end[0]) ||
                (nums[i] >= notes[k].start[1] && nums[i] <= notes[k].end[1]))
                    {
                        validnum = 1;
                        break;
                    }
            }
            // if nums didn't match field, add number to part 1 sum (and mark ticket as invalid for part2)
            if (!validnum)
            {
                badvalues += nums[i];
                validticket = 0;
            }
        }
        // check for part 2
        if (validticket)
        {
            for (int i = 0; i < ct; i++)
            {
                for (int k = 0; k < FIELDS; k++)
                {
                    // if the number isn't in a valid range for that field, mark field as impossible
                    if (!((nums[i] >= notes[k].start[0] && nums[i] <= notes[k].end[0]) ||
                        (nums[i] >= notes[k].start[1] && nums[i] <= notes[k].end[1])))
                    {
                        fieldposs[i][k] = 0;
                    }
                }
            }
        }
    }
    fclose(f);

    printf("\nPart 1: %i\n", badvalues);

    // iterate over the possibilities matrix and if a row (ticket position) has only one possibility
    // mark that field as impossible for all the other rows, until we end up with only
    // one possibility per row
    for (int i = 0; i < FIELDS; i++)
    {
        checkrows(FIELDS,FIELDS,fieldposs);
    }


    long solution = 1;
    for (int i = 0; i < FIELDS; i++)
    {
        if (strstr(notes[i].desc, "departure"))
        {
            for (int j = 0; j < FIELDS; j++)
            {
                if (fieldposs[j][i] == 1)
                {
                    // printf("%i:%i - %s: %i\n", i, j, notes[i].desc, ticket[j]);
                    solution *= ticket[j];
                }
            }
        }
    }
    printf("Part 2: %li\n", solution);


}

void checkrows(int rows, int cols, int pos[rows][cols])
{
    int count = 0, mark = -1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (pos[i][j] == 1)
            {
                count++;
                mark = j;
            }
        }
        //printf("row %i: %i\n", i, count);
        // if there's only one possibility, mark all other rows using that field as impossible
        if (count == 1)
        {
            for (int k = 0; k < FIELDS; k++)
            {
                if (k != i)
                    pos[k][mark] = 0;
            }
        }
        count = 0;
    }
    return;
}
