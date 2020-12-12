// Advent of Code - Day 11
// @curiouskiwi
// 12 Dec 2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


int partone(int h, int w, char temp[h][w], char spots[h][w]);
int parttwo(int h, int w, char temp[h][w], char spots[h][w]);
bool taken(char c);
bool empty(char c);
int occupyct(int h, int w, char spots[h][w]);
void copyseats(int h, int w, char dest[h][w], char src[h][w]);
void printseats(int h, int w, char s[h][w]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage:  ./solve [part]\n");
        return -1;
    }

    int choice = atoi(argv[1]);
    if (choice < 1 || choice > 2)
    {
        printf("choice is 1 or 2\n");
        return -1;
    }

    int width = 94; //94; // 10
    int height = 93; //93;// 10

    FILE *f = fopen("data.txt", "r");
    if (!f)
    {
        printf("couldn't open data file\n");
        return -1;
    }

    // has +2 to hold the newline and nul char but we'll ignore those going forward
    char (*spots)[width] = calloc(height, width+2);

    for (int i = 0; i < height; i++)
        fgets(spots[i], width+2, f);

    fclose(f);
    // printseats(height, width, spots);

    // temp array
    char temp[height][width];
    copyseats(height, width, temp, spots);

    int switches = 0;
    do
    {
        if (choice == 1)
            switches = partone(height, width, temp, spots);
        else
            switches = parttwo(height, width, temp, spots);
    }
    while (switches);

    printf("Part %i: %i\n", choice, occupyct(height, width, spots));

    free(spots);
}


int partone (int h, int w, char temp[h][w], char spots[h][w])
{
    // If a seat is empty (L) and there are no occupied seats adjacent to it,
    // the seat becomes occupied.
    // If a seat is occupied (#) and four or more seats adjacent to it are also
    // occupied, the seat becomes empty.
    // Otherwise, the seat's state does not change.

    int switches = 0;
    // variables to hold the up/down/around values
    int xmin, xmax, ymin, ymax;

    // iterate over rows
    for (int i = 0; i < h; i++)
    {
        // if we are on the top or bottom row
        ymin = (i == 0) ? 0 : -1;
        ymax = (i == h - 1) ? 0 : 1;

        // iterate over columns
        for (int j = 0; j < w; j++)
        {
            // if we are on the left or right side column
            xmin = (j == 0) ? 0 : -1;
            xmax = (j == w - 1) ? 0 : 1;

            //printf("%i:%i:%c\n", i, j, spots[i][j]);
            //iterate over surrounding seats
            char seat = spots[i][j];
            if (seat != '.')
            {
                int countL = 0, countS = 0, count = 0;
                for (int y = ymin; y <= ymax; y++)
                {
                    for (int x = xmin; x <= xmax; x++)
                    {
                        char chk = spots[i+y][j+x];
                        

                        // don't want to check the actual seat
                        if (!(y == 0 && x == 0))
                        {
                            if (chk != '.')
                                count++;

                            // we want to check this one
                            if (empty(chk))
                                countL++;
                            else if(taken(chk))
                                countS++;
                        }
                    }
                }
                // if seat is empty and no occupied adjacent, change to #
                if (empty(seat) && countL == count)
                {
                    temp[i][j] = '#';
                    switches++;
                }
                // if seat is occupied and 4+ seats are also occupied, set to L
                if (taken(seat) && countS >= 4)
                {
                    temp[i][j] = 'L';
                    switches++;
                }
            }
        }
    }

    // printf("switches: %i\n", switches);
    //switches = 0;
    copyseats(h, w, spots, temp);

    //printseats(height, width, spots);
    //printf("occupied: %i\n", occupied);

    return switches;
}


int parttwo(int h, int w, char temp[h][w], char spots[h][w])
{
    // the eight directions we'll be searching
    struct
    {
        int dx;
        int dy;
        int xLim;
        int yLim;
    }
    dir[8] = {
                {-1, -1, -1, -1},  // left/up
                {+1, -1,  w, -1},    // right/up
                {+1, +1,  w,  h},     // right/down
                {-1, +1, -1,  h},    // left/down
                {-1,  0, -1, -1},    // left
                {+1,  0,  w, -1},     // right
                {0,  -1, -1, -1},    // up
                {0,  +1, -1,  h}      // down
            };

    int switches = 0;
    int countL, countS, checked;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // this is the seat to check from
            char seat = spots[i][j];
            countL = countS = checked = 0;
            if (seat != '.')
            {
                int x, y;
                // look in all 8 directions
                for (int d = 0; d < 8; d++)
                {
                    // skip over the spots that are not seats
                    for (y = i+dir[d].dy, x = j+dir[d].dx;  y != dir[d].yLim && x != dir[d].xLim && spots[y][x] == '.';  y+=dir[d].dy), x+=dir[d].dx;

                    // we've found a seat
                    if (y != dir[d].yLim && x != dir[d].xLim)
                    {
                        checked++;
                        if (empty(spots[y][x]))
                            countL++;
                        else if (taken(spots[y][x]))
                            countS++;
                    }
                }

                // printf("%c:%i%i: L: %i S: %i chk: %i\n", seat, i, j, countL, countS, checked);
                // if seat is empty and no occupied seen, change to #
                if (empty(seat) && countL == checked)
                {
                    temp[i][j] = '#';
                    switches++;
                }
                // if seat is occupied and 5+ seats are also occupied, set to L
                if (taken(seat) && countS >= 5)
                {
                    temp[i][j] = 'L';
                    switches++;
                }
            }
        }
    }

    // set the spots to the new values for next round
    copyseats(h, w, spots, temp);

    return switches;
}


bool taken(char c)
{
    return c == '#';
}


bool empty(char c)
{
    return c == 'L';
}

int occupyct(int h, int w, char spots[h][w])
{
    int occupied = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (taken(spots[i][j]))
                occupied++;
        }
    }
    return occupied;
}

void copyseats(int h, int w, char dest[h][w], char src[h][w])
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}


void printseats(int h, int w, char s[h][w])
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf("%c", s[i][j]);
        }
        printf("\n");

    }
    printf("________________\n");
}
