#Advent of Code - Day 13
#@curiouskiwi / @gary_anderson
#13 Dec 2020

#explanations are in the C version :)

import csv


def main():
    # from the file
    timestamp = 1011416

    with open("data.csv") as f:
        lines = csv.reader(f)

        buses = []
        for line in lines:
            for i, item in enumerate(line):
                if item != 'x':
                    buses.append((i, int(item)))
    num = len(buses)

    # Part 1
    p1 = 0;
    min = timestamp;
    minbus = 0;
    for i in range(num):
        bus = buses[i][1]
        p1 = ((timestamp % bus) - bus) * -1
        if p1 < min:
            min = p1
            minbus = i

    print("Part 1: ", min * buses[minbus][1]);

    # Part 2

    buses_so_far = buses[0][1]
    t = 0
    for i in range(1, num):
        bus = buses[i][1]
        gap = buses[i][0]

        t = timebus(buses_so_far, bus, gap + t) + t
        buses_so_far *= bus

    print("Part 2: ", t)



def timebus(bus, next_bus, gap):

    j = 0
    for i in range(0, bus*next_bus, bus):
        if j < i+gap:
            j+= ((i+gap-j)//next_bus)* next_bus
        if i+gap == j:
            return i
    return 0


main()
