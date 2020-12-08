# Advent of Code 2020 - Day 7
# @curiouskiwi
# 8 Dec

import re


def main():

    with open("data.txt") as f:
        lines = f.readlines()

    colour = "shiny gold"
    bags(colour, lines)
    print("Part 1: ", len(set(rows)))

    # don't include the initial bag, so subtract one
    answer = getthem(colour, lines) - 1
    print("Part 2: ", answer)


# for part 1
rows = []


def bags(s, lines):
    for line in lines:
        if s in line[1:]:
            l = line[0:line.find("bag")]
            rows.append(l)
            bags(l, lines)


# gets the info about what's in the bag
def inbag(s, lines):
    for line in lines:
        mainbag = re.search("^\\w+ \\w+", line)
        if s in mainbag.group():
            return mainbag.string


# gets the bags in the bag
def contents(line):
    stuff = []
    contents = re.findall("(\d \w+ \w+)", line)
    for item in contents:
        num = re.search("^\d", item).group()
        bags = re.findall("[a-z]+ [a-z]+", item)

        for item in bags:
            ans = num, item
        stuff.append(ans)

    return stuff


# counts the number of bags in the bags in the bags ...
def getthem(s, lines):
    counter = 1
    thebag = inbag(s, lines)
    things = contents(thebag)
    # if this bag has more bags, keep going deeper
    if things:
        for thing in things:
            counter += (int(thing[0]) * getthem(thing[1], lines))

    return counter
    # this will include the first bag


main()
