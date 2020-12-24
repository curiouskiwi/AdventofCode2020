// Advent of Code - Day 24
// @curiouskiwi  @gary_anderson
// 24 Dec 2020

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FILENAME "data.txt"
//#define FILENAME "sample.txt"
#define LINE 50
#define DIM 200

bool tilearea[DIM][DIM] = {{false}};

int countblacktiles();

int main(void)
{
    FILE *file = fopen(FILENAME, "r");
    if (!file) return -1;

    char buffer[LINE];
    while(fgets(buffer, sizeof(buffer), file))
    {
        int x = DIM/2; int y = DIM/2; char *ptr = buffer;
        // sesenwnenenewseeswwswswwnenewsewsw
        while (*ptr != '\n')
        {
            switch (*ptr)
            {
                // e, se, sw, w, nw, ne
                case 'e': x++; break;

                case 'w': x--; break;

                case 'n': y++; ptr++;

                    if (*ptr == 'e')
                        x++;
                    break;

                    // else if (*ptr) == 'w')
                    //      break;


                case 's': y--; ptr++;

                    if (*ptr == 'w')
                        x--;
                    break;

            }
            ptr++;
        }
        tilearea[x][y] = !tilearea[x][y];
    }
    fclose(file);

    printf("Part 1; %i\n", countblacktiles());

    // PART 2
    bool copyarea[DIM][DIM];
    for (int c = 0; c < 100; c++)
    {
        memcpy(copyarea, tilearea, sizeof(copyarea));

        for (int x = 1; x < DIM-1; x++)
        {
            for (int y = 1; y < DIM-1; y++)
            {
                int counter = 0;
                if (copyarea[x][y+1]) counter++;
                if (copyarea[x+1][y+1]) counter++;
                if (copyarea[x+1][y]) counter++;
                if (copyarea[x][y-1]) counter++;
                if (copyarea[x-1][y-1]) counter++;
                if (copyarea[x-1][y]) counter++;

                if (copyarea[x][y])
                {
                    if (counter == 0 || counter > 2)
                        tilearea[x][y] = false;
                }
                else
                {
                    if (counter == 2)
                        tilearea[x][y] = true;
                }
            }
        }
    }

    printf("Part 2: %i\n", countblacktiles());
}


// black tiles are 'true'
int countblacktiles()
{
    int count = 0;
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            if (tilearea[i][j])
            {
                count++;
            }
        }
    }
    return count;
}
