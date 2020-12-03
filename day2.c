// Advent of Code Day 2
// @curiouskiwi
// 3 Dec 2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// assumptions based on looking at data file
#define MAXLINELENGTH 35
#define MAXPASSWORD 30

typedef struct puzzle
{
    int min;
    int max;
    char c;
    char password[MAXPASSWORD];
}
PUZZLE;

PUZZLE *parse(char *line);
bool check(PUZZLE *item, int choice);


int main(int argc, char *argv[])
{
    // get choice from user
    if (argc != 2)
    {
        printf("choose 1 or 2\n");
        return -1;
    }
    int choice = atoi(argv[1]);
    if (choice != 1 && choice != 2)
    {
        printf("choose 1 or 2\n");
        return -1;
    }

    // open data file
    FILE *file = fopen("data.txt", "r");

    int meetsreqs = 0;

    // prepare to read in each line to be parsed and checked
    char buff[MAXLINELENGTH];
    int index = 0;
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        if (c != '\n')
        {
            // Append character to buff
            buff[index] = c;
            index++;
        }
        else if (index > 0)
        {
            // end the string
            buff[index] = 0;

            // parse the line into values
            PUZZLE *line = parse(buff);

            // check if line meets the requirements
            if (check(line, choice))
            {
                meetsreqs++;
            }

            // get ready for next line
            free(line);
            index = 0;
        }
    }

    // done so we can close the file
    fclose(file);

    // print the results
    printf("Meets Part %i:  %i\n", choice, meetsreqs);
}

// check if the line meets the requirements
// assumes that data from file meets the spec, so no error checking
bool check(PUZZLE *item, int choice)
{
    char *p = item->password;
    char c = item->c;
    int len = strlen(p);
    int min = item->min;
    int max = item->max;
    int count = 0;

    // choice 1 checks if c appears min-max times
    if (choice == 1)
    {
        for (int j = 0; j < len; j++)
        {
            if (p[j] == c)
            {
                count++;
            }
        }
        if (count >= min && count <= max)
        {
            return true;
        }
    }

    // choice 2 checks if c appears only once in positions first/sec
    else
    {
        // not zero indexed so adjust
        int first = min - 1;
        int sec = max - 1;

        if ((p[first] == c && p[sec] != c) || (p[first] != c && p[sec] == c))
        {
            return true;
        }
    }
    return false;
}

// parses a given line like "1-3 r: rzqrmz" into elements
// assumes that line will meet that format as given
PUZZLE *parse(char *line)
{
    // create struct to hold the elements
    PUZZLE *p = malloc(sizeof(PUZZLE));

    // set the min and max values
    p->min = atoi(strtok(line, "-")) ;
    p->max = atoi(strtok(NULL, " "));

    // only want first char for c
    p->c = strtok(NULL, ":")[0];

    // +1 to get rid of leading space
    strcpy(p->password, (strtok(NULL, "")) + 1);

    return p;
}
