# Advent of Code 2020 - Day 8
# @curiouskiwi
# 8 Dec 2020


def main():

    with open("data.txt") as f:
        lines = f.readlines()

    ex = len(lines)

    instructions = []

    # example input:  jmp +248
    for line in lines:
        l = []
        # instruction
        l.append(line.split()[0])
        # argument
        l.append(int(line.split()[1]))
        # visited flag
        l.append(0)
        instructions.append(l)

    # Part 1 should return false
    if runcode(instructions, ex):
        print("returned true")
    else:
        print("returned false")

    # Part 2
    # change each jmp to nop and test
    for i in range(ex):
        if instructions[i][0] == 'jmp':
            instructions[i][0] = 'nop'
            if (runcode(instructions, ex)):
                print("returned true")
                break
            else:
                instructions[i][0] = 'jmp'
    print("completed all jmp")

    # if that doesn't return true, try 'nop' -> 'jmp'


def runcode(instructions, ex):

    # reset all lines to unvisited
    for item in instructions:
        item[2] = 0

    visited = 0
    linenum = 0
    accumulator = 0
    while True:
        # if we've reached the end, no infinite loop!
        if linenum >= ex:
            print(visited, linenum, accumulator)
            return True
        # if we hit an already visited instruction, infinite loop. :(
        if instructions[linenum][2] == 1:
            print(visited, linenum, accumulator)
            return False

        # we've seen this instruction now
        instructions[linenum][2] = 1

        visited += 1
        if instructions[linenum][0] == 'nop':
            linenum += 1
        elif instructions[linenum][0] == 'acc':
            accumulator += instructions[linenum][1]
            linenum += 1
        elif instructions[linenum][0] == 'jmp':
            linenum += instructions[linenum][1]
        else:
            print("we have a problem")


main()
