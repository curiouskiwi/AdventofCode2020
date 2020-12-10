# Advent of Code - Day 10
# @curiouskiwi
# 10 Sep 2020

with open("data.txt") as f:
    lines = f.readlines()

nums = [int(i) for i in lines]
nums.insert(0, 0)
nums.sort()
builtin = max(nums) + 3
nums.append(builtin)

# print(nums)
# [0, 1, 2, 3, 4, 7, 10, 11, 12, 13, 16, 17, 18, 19, 20, 23, 24, 25, 26, 29, 30,
#  31, 34, 35, 36, 37, 40, 41, 42, 45, 48, 49, 50, 51, 54, 57, 58, 59, 62, 65, 66,
#  67, 68, 69, 72, 73, 74, 75, 78, 79, 80, 83, 84, 85, 88, 89, 90, 91, 94, 95, 96,
#  97, 100, 103, 104, 105, 106, 107, 110, 111, 112, 115, 116, 117, 118, 119, 122,
#  125, 126, 127, 128, 129, 132, 135, 136, 137, 138, 141, 142, 145, 146, 149, 152,
#  155, 156, 157, 158, 159, 162, 163, 164, 165, 166, 169, 170, 171, 172, 175]

ones = 0
threes = 0
combos = 1;

#longest run of 1 in data is 5 so these are number of combos for each
    #   0, 1, 2, 3, 4
    #   0, 1, 2,    4
    #   0, 1,    3, 4
    #   0, 1,       4
    #   0,    2, 3, 4
    #   0,    2,    4
    #   0,       3, 4
    #   0,          4 - invalid
    #  if count is 4, 7
    #  if count is 3, 4
    #  if count is 2, 2
    #  if count is 1, 1

possibilities = [1, 1, 2, 4, 7]
start = 0

for i in range(1, len(nums)):
    if nums[i] - nums[i-1] == 1:
        ones += 1
    elif nums[i] -nums[i-1] == 3:
        threes += 1
        combos *= possibilities[(i-1 - start)]
        start = i

print("Part 1: ", ones * threes)
print("Part 2: ", combos)
