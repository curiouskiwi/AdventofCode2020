// Advent of Code Day 2
// @curiouskiwi
// 3 Dec 2020

// For choice 1:
// Each line gives the password policy and then the password.
// The password policy indicates the lowest and highest number of
// times a given letter must appear for the password to be valid.
// For example, 1-3 a means that the password must contain a at
// least 1 time and at most 3 times.

// For choice 2:
// Each policy actually describes two positions in the password,
// where 1 means the first character, 2 means the second character,
// and so on. (Be careful; Toboggan Corporate Policies have no concept of "index zero"!)
// Exactly one of these positions must contain the given letter.
// Other occurrences of the letter are irrelevant for the purposes of policy enforcement.


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

    // storage for line
    PUZZLE p;

    while (fgets(buff, MAXLINELENGTH, file))
    {
        sscanf(buff, "%d-%d %c: %s\n", &p.min, &p.max, &p.c, p.password);
        // check if line meets the requirements
        if (check(&p, choice)) meetsreqs++;
    }
    // done so we can close the file
    fclose(file);

    // print the results
    printf("Meets Part %i:  %i\n", choice, meetsreqs);
}

// check if the line meets the requirements
// assumes that data from file meets the spec, so no error checking
bool check(PUZZLE *p, int choice)
{
    int count = 0;

    // choice 1 checks if c appears min-max times
    if (choice == 1)
    {
        for (char *q = p->password; *q; q++)
            if (*q == p->c) count++;
        return (count >= p->min && count <= p->max);
    }

    // choice 2 checks if c appears only once in positions first/sec
    else
    {
        return ((p->password[p->min-1] == p->c) ^ (p->password[p->max-1] == p->c));
    }
}

