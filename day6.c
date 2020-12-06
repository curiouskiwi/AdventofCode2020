// Advent of Code 2020 - Day 6
// @curiouskiwi
// 6 Dec 2020

#include <stdio.h>
#include <string.h>

#define LEN 26

int count(char *s, char ch);

int main(void)
{

    // open data file
    FILE *file = fopen("data.txt", "r");
    if (!file) return 1;
    // prepare to read in each line to be parsed and checked
    char buff[LEN+2] = {0};
    char form[LEN * 20] = {0};
    int first = 0, second = 0, num = 0;

    while (fgets(buff, sizeof(buff), file))
    {
        if (buff[0] != '\n')
        {
            strcat(form, buff);
            num++;
        }
        // new form
        else
        {
            // loop over alphabet
            for (int i = 0; i < 26; i++)
            {
                // part 1. strchr only finds first one so counts unique
                if (strchr(form, i+'a')) first++;

                // part 2. count will find all, so if == num, then everyone has said yes
                if (count(form, i+'a') == num) second++;
            }
            // ready for next form
            form[0] = '\0';
            num = 0;
        }
    }
    printf("part 1: %i\npart 2: %i\n", first, second);
}


// counts all occurrence of a char in a string
int count(char *s, char ch)
{
    int ct = 0;
    char c;
    while ((c = *s++))
    {
        if (c == ch) ct++;
    }
    return ct;
}
