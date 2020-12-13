// Advent of Code - Day 13
// @curiouskiwi & @gary_anderson
// 13 Dec 2020

#include <stdio.h>

long timebus(long bus, long next_bus, long gap);

int main(void)
{

    int bus[] = {41,37,911,13,17,23,29,827,19};
    int gap[] = {0,35,41,54,55,64,70,72,91};

    // int bus[] = {17,13,19};
    // int gap[] = {0, 2, 3};

    int size = sizeof(bus)/ sizeof(bus[0]);

    long buses_so_far = bus[0];
    long t = 0;
    for (int i = 1; i < size; i++)
    {
        printf("t = timebus(%li, %i, %i + %li) + %li\n", buses_so_far, bus[i], gap[i], t, t);
        t = timebus(buses_so_far, bus[i], gap[i] + t) + t;
        buses_so_far *= bus[i];
    }
    printf("t: %li\n", t);
}


long timebus(long bus, long next_bus, long gap)
{
    for (long i = 0, j = 0; i < bus * next_bus; i += bus)
    {
        if (j < i + gap)
        {
            j += ((i + gap - j)/next_bus) * next_bus;
        }
        // printf("i: %li j: %li\n", i, j);
        if (i + gap == j)
        {
            return i;
        }
   }
   return 0;
}

// solution run
// t = timebus(41, 37, 35 + 0) + 0
// t = timebus(1517, 911, 41 + 779) + 779
// t = timebus(1381987, 13, 54 + 933734) + 933734
// t = timebus(17965831, 17, 55 + 9225656) + 9225656
// t = timebus(305419127, 23, 64 + 134986473) + 134986473
// t = timebus(7024639921, 29, 70 + 5327111632) + 5327111632
// t = timebus(203714557709, 827, 72 + 173918469736) + 173918469736
// t = timebus(168471939225343, 19, 91 + 135440384788512) + 135440384788512
// t: 640856202464541



/*** EXPLANATION ***/

// Example data:  the list 17,x,13,19
// if bus 0 is every 17 mins and bus 2 is every 13 mins, then each 17 * 13 minutes,
// the 2 buses will arrive together.  (ie, it repeats every 17*13=221 minutes)
// So we're searching for a multiple of 13 that is 2 greater (the gap) than a multiple of 17.
// i   j
// 17  13
// 34  26
// 51  52
// 68  65
// 85  78
// 102 104  i+gap == j  return 102 + 0 (the first bus gap)
//
//  so that's what we get with calling s(17, 13, 2 + 0) + 0
// i: 0 j: 0
// i: 17 j: 13
// i: 34 j: 26
// i: 51 j: 52
// i: 68 j: 65
// i: 85 j: 78
// i: 102 j: 104
//


// now we have a "composite bus" that arrives every 221 minutes.  At minute 105 (ie, 102+3) we want
// the next bus (19) to arrive.
// t = s(221, 19, 3 + 102) + 102

// i: 0 j: 95
// i: 221 j: 323
// i: 442 j: 532
// i: 663 j: 760
// i: 884 j: 988
// i: 1105 j: 1197
// i: 1326 j: 1425
// i: 1547 j: 1634
// i: 1768 j: 1862
// i: 1989 j: 2090
// i: 2210 j: 2299
// i: 2431 j: 2527
// i: 2652 j: 2755
// i: 2873 j: 2964
// i: 3094 j: 3192
// i: 3315 j: 3420  // 3315+105==3420

// t: 3417 return 3315+102  (we need to add the composite bus's gap)

// if we have more buses, we keep doing the same, creating a "composite bus" representing all
// the buses we've already taken into account.

// other testing done manually

// long t = s(17, 13, 2);
// long x = s(17*13, 19, t+3) + t;
// printf("%li\n", x); // 3417


// long a = s(67, 7, 1);
// long b = s(67*7, 59, a+2) + a;
// long c = s(67*7*59, 61, b+3) + b;
// printf("%li\n", c);  // 754018

// long d = s(67, 7, 2);
// long e = s(67*7, 59, d+3) + d;
// long f = s(67*7*59, 61, e+4) + e;
// printf("%li\n", f); // 779210
