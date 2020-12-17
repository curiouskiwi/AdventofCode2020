// Advent of Code - Day 17 - part 2
// @curiouskiwi
// 17 Dec 2020

// for part 1, remove the W dimension from the array
// and from the nested loops.

#include <stdio.h>
#include <string.h>
#define DIM 8
#define ROUNDS 6
#define DIMX (DIM + (ROUNDS+1)*2)
#define DIMY DIMX
#define DIMZ (1 + (ROUNDS+1)*2)
#define DIMW DIMZ

int main(void)
{
    char *t[DIM] = {
        "..##.#.#",
        "##....#.",
        "....####",
        "#..##...",
        "#..#.##.",
        ".#..#...",
        "##...##.",
        ".#...#.."
        };

    // to avoid running over the edge when doing the 'look around'
    // give the array a one-int buffer all around
    int space [DIMX][DIMY][DIMZ][DIMW] = {0};
    for (int x = 0; x < DIM; x++)
        for (int y = 0; y < DIM; y++)
            if (t[x][y] == '#')
                space[ROUNDS+1+x][ROUNDS+1+y][ROUNDS+1][ROUNDS+1] = 1;

    // RULES:
    //If a cube is active and exactly 2 or 3 of its neighbors are also active,
    // the cube remains active. Otherwise, the cube becomes inactive.
    // If a cube is inactive but exactly 3 of its neighbors are active,
    // the cube becomes active. Otherwise, the cube remains inactive.


    int spacecpy[DIMX][DIMY][DIMZ][DIMW];
    int ct = 0;
    for (int round = 0; round < ROUNDS; round++)
    {
        // we need a copy of the matrix so we don't affect calculations as we go
        memcpy(spacecpy, space,sizeof(space));
        for (int x = 1; x < DIMX-1; x++)
            for (int y =1; y < DIMY-1; y++)
                for (int z = 1; z < DIMZ-1; z++)
                    for (int w = 1; w < DIMW-1; w++)
                    {
                        // okay now do the look around +/- 1 spot and count
                        ct = 0;
                        for (int dx = -1; dx <= 1; dx++)
                            for (int dy = -1; dy <= 1; dy++)
                                for (int dz = -1; dz <= 1; dz++)
                                    for (int dw = -1; dw <= 1; dw++)
                                        ct += space[x+dx][y+dy][z+dz][w+dw];

                        // don't count the origin
                        ct -= space[x][y][z][w];
                        if (space[x][y][z][w] == 1)
                        {
                           if (ct < 2 || ct > 3)
                              spacecpy[x][y][z][w] = 0;
                        }
                        else
                            if (ct == 3)
                                spacecpy[x][y][z][w] = 1;
                    }
        // now copy the changes to the space matrix ready for next round
        memcpy(space, spacecpy, sizeof(space));
    }

    int results = 0;

    // iterate over full array and count
    for (int x = 1; x < DIMX-1; x++)
        for (int y = 1; y < DIMY-1; y++)
            for (int z = 1; z < DIMZ-1; z++)
                for (int w = 1; w < DIMW-1; w++)
                    results+= space[x][y][z][w];

    printf("Part 2: %i\n", results);
}
