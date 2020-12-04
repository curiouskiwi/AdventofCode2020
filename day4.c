// Advent of Code 2020 - Day 4
// @curiouskiwi
// 4 Dec 2020


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINELENGTH 100
#define PASSPORTLEN 500


bool byr (char *s);
bool iyr (char *s);
bool eyr (char *s);
bool hgt (char *s);
bool hcl (char *s);
bool ecl (char *s);
bool pid (char *s);

int main(void)
{
    // open data file
    FILE *file = fopen("data.txt", "r");
    if (!file) return 1;

    int meetsreqs = 0;

    // prepare to read in each line to be parsed and checked
    char passport[PASSPORTLEN] = {0};
    char buff[MAXLINELENGTH];

    while (fgets(buff, MAXLINELENGTH, file))
    {
        if (buff[0] != '\n')
        {
            strcat(passport, buff);
        }
        else
        {
            if (byr(passport) &&
                iyr(passport) &&
                eyr(passport) &&
                hgt(passport) &&
                hcl(passport) &&
                ecl(passport) &&
                pid(passport)
                )
                meetsreqs++;
            // reset passport for next one
            passport[0] = '\0';
        }
    }
    printf("%i\n", meetsreqs);
}


bool byr (char *s)
//(Birth Year) - four digits; at least 1920 and at most 2002.
{
    char *r = strstr(s, "byr:");
    if (!r) return false;

    int yr = atoi(r+4);
    return yr >= 1920 && yr <= 2002;
}


bool iyr (char *s)
//(Issue Year) - four digits; at least 2010 and at most 2020.
{
    char *r = strstr(s, "iyr:");
    if (!r) return false;

    int yr = atoi(r+4);
    return yr >= 2010 && yr <= 2020;
}


bool eyr (char *s)
//(Expiration Year) - four digits; at least 2020 and at most 2030.
{
    char *r = strstr(s, "eyr:");
    if (!r) return false;

    int yr = atoi(r+4);
    return yr >= 2020 && yr <= 2030;
}


bool hgt (char *s)
//(Height) - a number followed by either cm or in:
//If cm, the number must be at least 150 and at most 193.
//If in, the number must be at least 59 and at most 76.
{
    char *r = strstr(s, "hgt:");
    if (!r) return false;

    int h;
    char c, c1;

    if (sscanf(r+4, "%d%c%c", &h, &c, &c1) != 3)  return false;

    if (c == 'c' && c1 == 'm')
        return (h >= 150 && h <= 193);

    if (c == 'i' && c1 == 'n')
        return (h >= 59 && h <= 76);

    return false;
}


bool hcl (char *s)
//(Hair Color) - a # followed by exactly six characters 0-9 or a-f.
{
    char *r = strstr(s, "hcl:");
    if (!r) return false;

    int num = 0;
    sscanf(r+4, "#%*x%n", &num);
    return num == 7;
}


bool ecl (char *s)
//(Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
{
    char *r = strstr(s, "ecl:");
    if (!r) return false;
    if (!(isspace(r[7]))) return false;

    char *eyes[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for (int i = 0; i < 7; i++)
    {
        if (strncmp(r+4, eyes[i], 3) == 0)
            return true;
    }
    return false;
}


bool pid (char *s)
//(Passport ID) - a nine-digit number, including leading zeroes.
{
    char *r = strstr(s, "pid:");
    if (!r) return false;

    int num = 0;
    sscanf(r+4,"%*d%n", &num);
    return num == 9;
}
