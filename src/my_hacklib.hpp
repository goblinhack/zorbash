//      SCCS Id: @(#)hacklib.c  3.4     2002/12/13      */
// Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
// Copyright (c) Robert Patrick Rankin, 1991              */
// NetHack may be freely redistributed.  See license for details. */

#pragma once
#ifndef _MY_HACKLIB_HPP_
#define _MY_HACKLIB_HPP_
//
// moon period = 29.53058 days ~= 30, year = 365.2422 days
// days moon phase advances on first day of year compared to preceding year
//      = 365.2422 - 12*29.53058 ~= 11
// years in Metonic cycle (time until same phases fall on the same days of
//      the month) = 18.6 ~= 19
// moon phase on first day of year (epact) ~= (11*(year%19) + 29) % 30
//      (29 as initial condition)
// current phase in days = first day phase + days elapsed in year
// 6 moons ~= 177 days
// 177 ~= 8 reported phases * 22
// + 11/22 for rounding
//
#define NEW_MOON  0
#define FULL_MOON 4

extern int phase_of_the_moon(void); // 0-7, with 0: new, 4: full

extern int friday_13th(void);

extern int halloween(void);

extern int night(void);

extern int midnight(void);

extern int december(void);

extern int xmas(void);

extern int first_of_month(void);

extern int midnight_close(void);

extern int getyear(void);
#endif
