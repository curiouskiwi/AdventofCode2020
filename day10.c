// Advent of Code - Day 10
// @curiouskiwi
// 10 Dec 2020

#include <stdio.h>
#include <stdlib.h>

// add 2 to the number in the data file
#define NUMS 108

// max number in file has 3 digits, so +1 for the newline
#define DIGITS 4

void sort(int values[], int n);

int main(void)
{
    FILE *f = fopen("data.txt", "r");
    if (!f)
    {
        printf("couldn't open data file\n");
        return -1;
    }
    // need array to also have start at 0 and end at max+3
    int nums[NUMS] = {0};
    int max = 0;
    char tmp[DIGITS];
    // start filling array from nums[1]
    int ct = 1;
    while (fscanf(f, "%s", tmp) != EOF)
    {
        nums[ct] = atoi(tmp);
        if (nums[ct] > max)
        {
            max = nums[ct];
        }
        ct++;
    }

    // set final number to the built-in adaptor value (max + 3)
    nums[ct] = max + 3;

    // verify assumption on file length
    if (ct + 1 != NUMS)
    {
        printf("didn't read the number we thought!\n");
        return -1;
    }

    sort(nums, NUMS);

    int ones = 0, threes = 0, start = 0;
    long combos = 1;

    // longest run of 1 in data is 5 (see logic in comments below)
    int possibilities[5] = {1, 1, 2, 4, 7};

    for (int i = 1; i < NUMS; i++)
    {
        if (nums[i] - nums[i - 1] == 3)
        {
            threes++;
            combos *= possibilities[(i - 1 - start)];
            start = i;
        }
        else
        {
            ones++;
        }
    }
    printf("Part 1: %i\n", ones * threes);
    printf("Part 2: %ld\n", combos);
}


// Selection sort
void sort(int values[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i; j < n - 1; j++)
        {
            if (values[j + 1] < values[min])
            {
                min = j + 1;
            }
        }

        int temp = values[i];
        values[i] = values[min];
        values[min] = temp;
    }
}

/** EXPLANATION OF LOGIC

    if the maximum diff from one adaptor to the next is 3, then you know that if there's
 a gap of 3 in the data, there is no choice.
 If there's a gap of 1, though, that means (for that group), there's a choice of
 combinations you can use.  So looking at my data, the longest run of "diff of 1" adaptors
 was 5.    There are 8 ways you can combine those 5 and all but 1 would meet the
 requirement of between 1-3 gap:

        0, 1, 2, 3, 4
        0, 1, 2,    4
        0, 1,    3, 4
        0, 1,       4
        0,    2, 3, 4
        0,    2,    4
        0,       3, 4
        0,          4 - invalid

 similarly, with 4 adaptors in a row,  there are 4 valid combos;  with 3, there are 2, and with 2 there's only 1.
 So my possibilities array is just a lookup table to tell me how many combos are possible for a given group size.
 Now, as I linearly search through my adaptors, when I hit a gap of 1, I keep count of how many there are until I hit a 3, and lookup the combos possible.  The overall combo count is then multiplied by the possibilities for that group.  (if the gap is 3, there's only one possibility, so we don't need to worry about that, since multiplying by 1 won't matter.)

 As example using the sample data given:
 int smnums[] = {0, 1, 2, 3, 4, 7, 8, 9, 10, 11, 14, 17, 18, 19, 20, 23, 24, 25, 28, 31,
                   32, 33, 34, 35, 38, 39, 42, 45, 46, 47, 48, 49, 52};

 {0, 1, 2, 3, 4} *      (7 possibilities)
 {7, 8, 9, 10, 11} *    (7 )
 {17, 18, 19, 20} *     (4 )
 {23, 24, 25} *         (2 )
 {31, 32, 33, 34, 35} * (7 )
 {38, 39} *             (1 )
 {45, 46, 47, 48, 49}   (7 )

 = 7*7*4*2*7*1*7 = 19,208 possible combos

 Per spec:   In total, this set of adapters can connect the charging outlet to your device in 19208 distinct arrangements.
**/
