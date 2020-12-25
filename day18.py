# Advent of Code - Day 18
# @curiouskiwi / @gary_anderson
# 25 Dec 2020 


def main():
    with open("data.txt", "r") as f:
        lines = f.readlines()
    sum1 = 0
    sum2 = 0
    for line in lines:
        sum1 += parseeq(line, 1)
        sum2 += parseeq(line, 2)
    print(f"Part 1: {sum1}\nPart 2: {sum2}")


def parseeq (text, part):
    while True:
        start = text.rfind('(')
        if start == -1:
            break
        end = text[start:].find(')')
        n = str(calc(text[start+1:start+end],part))
        text = text[:start] + n + text[start+end+1:]

    return calc(text,part)


def calc(eq, part):
    op = 'x'
    result = 0
    interim = 1
    for c in eq.split():
        try:
            if op == 'x':
                result = int(c)
            else:
                if op == '+':
                    result += int(c)
                else:
                    if part == 2:
                        interim *= result
                        result = int(c)
                    else:
                        result *= int(c)

                op = 'x'
        except:
            op = c

    return result * interim


main()
