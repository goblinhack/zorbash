import random


#
# Create dice rolls that understands;
#
# dice("d6"))
# dice("3d6"))
# dice("4d6+3"))
#
def roll(s):
    tot = 0
    for x in s.split('+'):

        d = x.split('d')
        if len(d) == 2:
            a = 1
            if d[0] != "":
                a = int(d[0])

            b = 1
            if d[1] != "":
                b = int(d[1])

            while a > 0:
                tot += random.randint(1, b)
                a -= 1
        else:
            tot += int(d[0])

    return tot
