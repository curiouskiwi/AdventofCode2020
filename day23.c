// Advent of Code - Day 23
// @curiouskiwi @gary_anderson
// 23 Dec 2020


#include <stdio.h>
// #define NUMCUPS 9
#define NUMCUPS 1000000
typedef struct cup
{
    int value;
    struct cup *next;
}
cup;

cup c[NUMCUPS];


void printcups(cup *check);
int main(void)
{
    char *puzzle = "624397158";
    //char *puzzle = "389125467";
    cup *current;
    cup *removed;

    // **initialisation for part 1**
    // for (int i = 0; i < 9; i++)
    // {
    //     c[i].value = puzzle[i] - '0';
    //     c[i].next = &c[(i+1)%NUMCUPS];
    // }

    for (int i = 0; i < NUMCUPS; i++)
    {
        c[i].value = i+1;
        c[i].next = &c[(i+1)%NUMCUPS];
    }
    for (int i = 0; i < 8; i++)
    {
        c[puzzle[i]-'1'].next = &c[puzzle[i+1]-'1'];
    }

    c[puzzle[8]-'1'].next = &c[9];
    c[NUMCUPS-1].next = &c[puzzle[0]-'1'];


    current = &c[puzzle[0]-'1'];
    int counter = 0;
    while (counter < 10000000)
    {
        // printf("current = %d\n", current->value);
        removed = current->next;
        current->next = removed->next->next->next;

        int placetoput = current->value - 1;
        if (placetoput == 0) placetoput = NUMCUPS;
        while (removed->value == placetoput || removed->next->value == placetoput ||
            removed->next->next->value == placetoput)
            {
            placetoput--;
            if (placetoput == 0) placetoput = NUMCUPS;
            }
        // printf("pl: %i\n", placetoput);

        cup *newplace;
        // int i = 0;
        newplace = &c[placetoput-1];


        // while (newplace->value != placetoput)
        // {
        //     newplace = newplace->next;
        //     // printf("***\n");
        //     // if (++i==10) break;
        // }
        removed->next->next->next = newplace->next;
        newplace->next = removed;

        counter++;
        current = current->next;
    }

    while (current->value != 1)
        {
            current = current->next;
            // printf("***\n");
            // if (++i==10) break;
        }
    printf("For part 2: ");
    printf("%i- %i - %i \n", current->value, current->next->value, current->next->next->value);
    printf("%li\n", (long)current->next->value * current->next->next->value);

}

void printcups(cup *check)
{
    for (int i = 0; i < 9; i++)
    {
        printf("%i ->", check->value);
        check = check->next;

    }
    printf("\n");
}


