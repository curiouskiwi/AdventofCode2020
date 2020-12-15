# Advent of Code Day 15
# @curiouskiwi / @gary_anderson
# 15 Dec 2020

def main():

    nums = {6:1, 3:2, 15:3, 13:4, 1:5, 0:7}

    previndex = 6
    turn = 7
    thisnum = 0

    # change to 2020 for part 1
    while turn < 30000000:
        if previndex != 0:
            thisnum = turn - previndex
        else:
            thisnum = 0
        turn+=1
        # add key to dict if not already there
        try:
            previndex = nums[thisnum]
        except KeyError:
            previndex = 0
        nums[thisnum] = turn
    print(thisnum)


import time
start_time = time.time()
main()
print("--- %s seconds ---" % (time.time() - start_time))
### takes about 18 seconds ###
