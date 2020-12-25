// Advent of Code - Day 14
// @curiouskiwi / @gary_anderson
// 25 Dec 2020 (did part 1 on 14 Dec)

#include <stdio.h>
#include <stdlib.h>

//#define FILENAME "smdata.txt"
#define FILENAME "data.txt"
// #define FILENAME "tiny.txt"

typedef struct node
{
    long address;
    long value;
    struct node *next;
}
node;

node *root = NULL;

node *findnode(long address);
void addnode(long address, long xMask, long data);

int main(void)
{
    long addresses[65536] = {0};
    char tmp[46];
    char bitmask[37];
    long address;
    long data;

    long xMask = 0, orMask = 0, andMask = 0;

    FILE *f = fopen(FILENAME, "r");

    while (fgets(tmp, sizeof(tmp), f))
    {
        //printf("read in %s\n", tmp);
        if (sscanf(tmp, "mask = %s", bitmask) == 1)
        {
            // 01111X0011X11110XX11X110111001X00001

            printf("read mask %s\n", bitmask);

            xMask = orMask = andMask = 0;
            for (int i = 0; i < 36; i++)
            {
                orMask <<= 1;
                xMask <<= 1;
                andMask <<= 1;
                if (bitmask[i] == '1')
                    orMask |= 1;
                if (bitmask[i] == 'X')
                    xMask |= 1;
                if (bitmask[i] != '0')
                    andMask |= 1;
            }
        }
        else
        {
            //mem[26252] = 2785
            if (sscanf(tmp, "mem[%li] = %li", &address, &data) == 2 )
            {
                // Part 1
                addresses[address] = (data & andMask) | orMask;

                // Part 2
                address |=  orMask;
                addnode(address, xMask, data);
            }
        }
    }
    fclose(f);

    long sum = 0;
    for (int i = 0; i < 65536; i++)
    {
        sum += addresses[i];
    }
    printf("Part 1: %li\n", sum);

    sum = 0;
    while (root)
    {
        sum += root->value;
        node *t = root;
        root = root->next;
        free(t);
    }
    // total heap usage: 80,125 allocs, 80,125 frees, 1,927,600 bytes allocated
    printf("Part 2: %li\n", sum);

}

void addnode(long address, long xMask, long data)
{
    if (xMask)
    {
        long bit = 0x1000000000;
        while ((xMask & bit) == 0)
        {
            bit >>= 1;
        }
        // printf("address: %lx\n", address);
        addnode(address & ~bit, xMask & ~bit, data);
        addnode(address | bit, xMask & ~bit, data);
    }
    else
    {
        node *t = findnode(address);
        if (t)
        {
            t->value = data;
        }
        else
        {
            t = malloc(sizeof(node));
            if (!t) {printf("couldn't make node\n"); return;}
            t->next = root;
            t->value = data;
            t->address = address;
            root = t;
            // printf("%09lx = %ld\n", address, data);

        }
    }

    return;
}

node *findnode(long address)
{
    node *cursor = root;
    while (cursor)
    {
        if (cursor->address == address)
        {
            return cursor;
        }
        cursor = cursor->next;
    }

    return NULL;
}
