// Advent of Code - Day 12
// @curiouskiwi
// 12 Dec 2020

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    FILE *f = fopen("data.txt", "r");
    if (!f)
    {
        printf("couldn't open data file\n");
        return -1;
    }

    // for part 1
    int lat = 0, lon = 0;
    int bearing = 90;

    // for part 2
    int lat2 = 0, lon2 = 0;
    int wayeast = 10;
    int waynorth = 1;

    // read in data and process as we go
    char data[6];
    while(fgets(data, sizeof(data), f))
    {
        int change = atoi(data+1);
        int tmp = 0;
        switch (data[0])
        {
            case 'N' :  lat += change;
                        waynorth += change;
                        break;

            case 'S' :  lat -= change;
                        waynorth -= change;
                        break;

            case 'E' :  lon += change;
                        wayeast += change;
                        break;

            case 'W' :  lon -= change;
                        wayeast -= change;
                        break;

            case 'L' :  bearing = (bearing - change + 360) % 360;
                        switch(change)
                        {
                            case 90: tmp = -waynorth; waynorth = wayeast; wayeast = tmp; break;
                            case 180: waynorth = -waynorth; wayeast = -wayeast; break;
                            case 270: tmp = waynorth; waynorth = -wayeast; wayeast = tmp; break;
                        }
                        break;

            case 'R' :  bearing = (bearing + change) % 360;
                        switch(change)
                        {
                            case 90: tmp = waynorth; waynorth = -wayeast; wayeast = tmp; break;
                            case 180: waynorth = -waynorth; wayeast = -wayeast; break;
                            case 270: tmp = -waynorth; waynorth = wayeast; wayeast = tmp; break;
                        }
                        break;

            case 'F' :  switch (bearing)
                        {
                            case 0: lat += change; break;
                            case 90: lon += change; break;
                            case 180: lat -= change; break;
                            case 270: lon -= change; break;
                        }
                        lat2 += change * waynorth;
                        lon2 += change * wayeast;
                        break;
        }
    }
    // done
    fclose(f);

    printf("Part 1: %i\n", abs(lat) + abs(lon));
    printf("Part 2: %i\n", abs(lat2) + abs(lon2));
}
