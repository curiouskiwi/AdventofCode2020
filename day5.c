// Advent of Code 2020 - Day 5
// @curiouskiwi
// 5 Dec 2020


#include <stdio.h>

#define MAXLINELENGTH 11
#define NUMSEATS 1024

int calcseat(char *buff);

int main(void)
{
    // open data file
    FILE *file = fopen("data.txt", "r");
    if (!file) return 1;


    char buff[MAXLINELENGTH];
    int seat_id = 0;
    int maxseat = 0;

    // array to hold which seats are taken
    int seats[NUMSEATS] = {0};

    // BFBFFFFLLL
    while(fscanf(file, "%s", buff) != EOF)
    {
        seat_id = calcseat(buff);
        seats[seat_id] = 1;

        if (seat_id > maxseat)
            maxseat = seat_id;
    }
    printf("maxseat: %i\n", maxseat);

    for (int i = 1; i < maxseat; i++)
    {
        if (seats[i] == 0 && seats[i-1] == 1 && seats[i+1] == 1)
        {
            printf("my seat: %i\n", i);
            break;
        }
    }
}


int calcseat(char *buff)
{
    int id = 0;
    for (int i = 0, start = 512; i < 10; i++, start /= 2)
        if (buff[i] == 'B' || buff[i] == 'R') id += start;
    return id;
}
