// Advent of Code - Day 9
// @curiouskiwi
// 10 Dec 2020

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// assumptions based on looking at data file
#define NUMS 1000
#define LENGTH 16
#define HISTORY 25

bool valid(long num[], long n);
long parttwo  (long nums[], long target, int max);
long weakness(long nums[], int length);
int main(void)
{
    long nums[NUMS];
    char tmp[LENGTH];

    FILE *f = fopen("data.txt", "r");
    if (!f) return 1;

    for (int i = 0; i < NUMS; i++)
    {
        fgets(tmp, LENGTH, f);
        nums[i] = atol(tmp);
    }

    long answer = 0;
    int i;
    for (i = HISTORY; i < NUMS; i++)
    {
        // find first one that doesn't meet requirements (sum of 2 in previous 25)
        if (!valid(&nums[i-HISTORY], nums[i]))
        {
            answer = nums[i];
            printf("Part 1: %ld\n", answer);
            break;
        }
    }

    // part 2
    for (i = 0; i < NUMS; i++)
    {
        // we test each consecutive list
        long result = parttwo(&nums[i], answer, NUMS - i);
        if (result)
        {
            printf("Part 2: %ld\n", result);
            break;
        }
    }

}

// check if n is the sum of 2 digits in previous 25 buckets
bool valid(long nums[], long n)
{
    for (int i = 0; i < HISTORY; i++)
    {
        for (int j = i + 1; j < HISTORY; j++)
        {
            if (nums[i] + nums[j] == n)
            {
                return true;
            }
        }
    }
    return false;
}
// given an array, add numbers until we hit the target sum (or return 0)
long parttwo  (long nums[], long target, int max)
{
    long sum = 0;
    for (int i = 0; i < max; i++)
    {
        sum += nums[i];
        if (sum > target)
            return 0;

        if (sum == target)
        {
            // range is 0 to i inclusive
            return weakness(nums, i);
        }
    }
    return 0;
}

// gets the min and max values in a given array and returns sum
long weakness(long nums[], int length)
{
    long min, max;
    min = max = nums[0];

    for (int i = 1; i <= length; i++)
    {
        if (nums[i] < min)
        {
            min = nums[i];
        }
        else if (nums[i] > max)
        {
            max = nums[i];
        }
    }
    return(min + max);
}
