// Advent of Code - Day 25
// @curiouskiwi / @gary_anderson
// 25 Dec 2020


#include <stdio.h>

#define SUBJECT 7

int main(void)
{
     long card = 8252394;
    //long card = 5764801;
     long door = 6269621;
    //long door = 17807724;
    // Set the value to itself multiplied by the subject number.
    // Set the value to the remainder after dividing the value by 20201227.
    int testcard = SUBJECT;
    int counter = 1;
    while (testcard != card)
    {
        testcard  = (testcard * SUBJECT) % 20201227;
        counter++;
    }
    int testdoor = SUBJECT;
    int counter1 = 1;
    while (testdoor != door)
    {
        testdoor = (testdoor * SUBJECT) % 20201227;
        counter1++;
    }
    // we actually only needed to do one of the above

    long encryptionkey = 1;

    for (int i = 0; i < counter1; i++)
        encryptionkey = (encryptionkey * card) % 20201227;

    printf("%li\n", encryptionkey);
}
