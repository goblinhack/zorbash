/*      SCCS Id: @(#)hacklib.c  3.4     2002/12/13      */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* Copyright (c) Robert Patrick Rankin, 1991              */
/* NetHack may be freely redistributed.  See license for details. */

#include "my_sys.h"

static struct tm *getlt (void)
{_
        time_t date;

#if defined(BSD) && !defined(POSIX_TYPES)
        (void) time((long *)(&date));
#else
        (void) time(&date);
#endif
#if (defined(ULTRIX) && !(defined(ULTRIX_PROTO) || defined(NHSTDC))) || (defined(BSD) && !defined(POSIX_TYPES))
        return(localtime((long *)(&date)));
#else
        return(localtime(&date));
#endif
}

/*
 * moon period = 29.53058 days ~= 30, year = 365.2422 days
 * days moon phase advances on first day of year compared to preceding year
 *      = 365.2422 - 12*29.53058 ~= 11
 * years in Metonic cycle (time until same phases fall on the same days of
 *      the month) = 18.6 ~= 19
 * moon phase on first day of year (epact) ~= (11*(year%19) + 29) % 30
 *      (29 as initial condition)
 * current phase in days = first day phase + days elapsed in year
 * 6 moons ~= 177 days
 * 177 ~= 8 reported phases * 22
 * + 11/22 for rounding
 */
int phase_of_the_moon (void)            /* 0-7, with 0: new, 4: full */
{_
        struct tm *lt = getlt();
        int epact, diy, goldn;

        diy = lt->tm_yday;
        goldn = (lt->tm_year % 19) + 1;
        epact = (11 * goldn + 18) % 30;
        if ((epact == 25 && goldn > 11) || epact == 24)
                epact++;

        return( (((((diy + epact) * 6) + 11) % 177) / 22) & 7 );
}

int friday_13th (void)
{_
        struct tm *lt = getlt();

        return((int)((lt->tm_wday == 5) /* friday */ && (lt->tm_mday == 13)));
}

int halloween (void)
{_
        struct tm *lt = getlt();

        return((int)((lt->tm_mday == 31) && (lt->tm_mon == 9)));
}

int night (void)
{_
        int hour = getlt()->tm_hour;

        return((hour < 6) || (hour > 21));
}

int december (void)
{_
        struct tm *lt = getlt();

        return((int)(lt->tm_mon == 11));
}

int xmas (void)
{_
        struct tm *lt = getlt();

        return((int)((lt->tm_mday == 25) && (lt->tm_mon == 11)));
}

int first_of_month (void)
{_
        struct tm *lt = getlt();

        return (int)((lt->tm_mday == 1));
}

int midnight (void)
{_
        return(getlt()->tm_hour == 0);
}

int midnight_close (void)
{_
        int hour = getlt()->tm_hour;

        return (hour > 23);
}

int getyear (void)
{_
        return(1900 + getlt()->tm_year);
}

