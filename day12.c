// Advent of Code - Day 12 - part 2
// @curiouskiwi
// 12 Dec 2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


int main(void)
{
    FILE *f = fopen("data.txt", "r");
    if (!f)
    {
        printf("couldn't open data file\n");
        return -1;
    }

    //int bearing = 90;
    int lat = 0, lon = 0;

    int wayeast = 10;
    int waynorth = 1;

    char data[6];
    while(fgets(data, sizeof(data), f))
    {
        int change = atoi(data+1);
        int tmp = 0;
        switch (data[0])
        {
            case 'N' : waynorth += change;
            break;

            case 'S' : waynorth -= change;
            break;

            case 'E' : wayeast += change;
            break;

            case 'W' : wayeast -= change;
            break;

            case 'L' : switch(change)
                        {
                            case 0: break;
                            case 90: tmp = -waynorth; waynorth = wayeast; wayeast = tmp; break;
                            case 180: waynorth = -waynorth; wayeast = -wayeast; break;
                            case 270: tmp = waynorth; waynorth = -wayeast; wayeast = tmp; break;
                        }
            break;

            case 'R' : switch(change)
                        {
                            case 0: break;
                            case 90: tmp = waynorth; waynorth = -wayeast; wayeast = tmp; break;
                            case 180: waynorth = -waynorth; wayeast = -wayeast; break;
                            case 270: tmp = -waynorth; waynorth = wayeast; wayeast = tmp; break;
                        }
            break;


            case 'F' : lat += change * waynorth;
                       lon += change * wayeast;
                       break;

        }
        printf("%s Lat: %i Lon: %i Waynorth: %i Wayeast: %i\n", data, lat, lon, waynorth, wayeast);
    }
    printf("Part 2: %i\n", abs(lat) + abs(lon));

    fclose(f);
}
