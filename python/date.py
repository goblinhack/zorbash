import datetime


def friday_13th():
    now = datetime.datetime.now()

    if now.weekday == 5 and now.day == 13:
        return True
    return False


def halloween():
    now = datetime.datetime.now()

    if now.month == 10 and now.day == 31:
        return True
    return False


def xmas():
    now = datetime.datetime.now()

    if now.month == 12 and now.day == 25:
        return True
    return False


# 0-7, with 0: new, 4: full */
# borrowed from nethack
def phase_of_the_moon(diy):
    now = datetime.datetime.now()
    time = now.timetuple()

    goldn = (time.tm_year % 19) + 1
    epact = (11 * goldn + 18) % 30
    if (epact == 25 and goldn > 11) or (epact == 24):
        epact += 1

    return (int(((((diy + epact) * 6) + 11) % 177) / 22) & 7)
