// Advent of Code - Day 15
// @curiouskiwi / @gary_anderson
// 15 Dec 2020


#include <stdio.h>

int nums[30000000] = {0};

int main(void)
{
// 6,3,15,13,1,0
    nums[6] = 1;
    nums[3] = 2;
    nums[15] = 3;
    nums[13] = 4;
    nums[1] = 5;
    nums[0] = 6;

    // next move will be
    nums[0] = 7;
    int previndex = 6;
    int turn = 7;
    int thisnum = 0;

    while (turn < 2020)
    {
        thisnum = (previndex) ? turn - previndex : 0;
        turn++;
        previndex = nums[thisnum];
        nums[thisnum] = turn;
    }
    printf("Part 1: %i\n", thisnum);

    while (turn < 30000000)
    {
        thisnum = (previndex) ? turn - previndex : 0;
        turn++;
        previndex = nums[thisnum];
        nums[thisnum] = turn;
    }
    printf("Part 2: %i\n", thisnum);
    //unique nums  //3611559
}
