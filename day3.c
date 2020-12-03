// Advent of Code Day 3
// @curiouskiwi
// 3 Dec 2020

// Test 1 has one slope
// Test 2 has 5 slopes
// Right 1, down 1.
// Right 3, down 1. (This is the slope you already checked.)
// Right 5, down 1.
// Right 7, down 1.
// Right 1, down 2.

#include <stdio.h>

// assumptions based on looking at data file
#define LINES 323
#define LENGTH 31

char lines[LINES][LENGTH+2];

int trees_hit(int down, int across);

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

    for (int i = 0; i < LINES; i++)
        fgets(lines[i], LENGTH+2, file);

    // done so we can close the file
    fclose(file);

   // do the rest
    if (choice == 1)
        printf("%d\n", trees_hit(1, 3));
    else
        printf("%ld\n", trees_hit(1, 1) * trees_hit(1, 3) * trees_hit(1, 5) * trees_hit(1, 7) * trees_hit(2, 1));
}

// calculate the number of trees hit based on the slope given
long trees_hit(int down, int across)
{
    long counter = 0;
    int pos = 0;
    for (int i = 0; i < LINES; i+=down)
    {
        if (lines[i][pos%LENGTH] == '#') counter++;
        pos += across;
    }
    return counter;
}
