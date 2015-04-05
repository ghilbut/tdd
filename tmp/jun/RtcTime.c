/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include "RtcTime.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

#define TEST 2

struct RtcTime
{
    int daysSince1980;
    int year;
    int dayOfYear;
    int month;
    int dayOfMonth;
    int dayOfWeek;
};

enum
{
    STARTING_YEAR = 1980, STARTING_WEEKDAY = Tuesday
};

static const int nonLeapYearDaysPerMonth[12] =
{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static const int leapYearDaysPerMonth[12] =
{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

BOOL IsLeapYear(int year)
{
    if (year % 400 == 0)
        return TRUE;
    if (year % 100 == 0)
        return FALSE;
    if (year % 4 == 0)
        return TRUE;
    return FALSE;
}

static int GetDaysInYear(int year)
{
    if (IsLeapYear(year))
        return 366;
    else
        return 365;
}


#if TEST < 2
void SetYearAndDayOfYear(RtcTime * time);
#else
void FirstSetYearAndDayOfYear(RtcTime * self);
#endif


static void ThenSetMonthAndDayOfMonth(RtcTime * self)
{
    int month = 0;
    int days = self->dayOfYear;
    const int * daysPerMonth = nonLeapYearDaysPerMonth;
    if (IsLeapYear(self->year))
        daysPerMonth = leapYearDaysPerMonth;

    while (days > daysPerMonth[month])
    {
        days -= daysPerMonth[month];
        month++;
    }
     self->month = month + 1;
     self->dayOfMonth = days;
}

static void setDayOfWeek(RtcTime * self)
{
     self->dayOfWeek =  ((self->daysSince1980-1)+STARTING_WEEKDAY)%7;
}


static void initRtcTime(RtcTime * self)
{
#if TEST < 2
    SetYearAndDayOfYear(self);
#else
	FirstSetYearAndDayOfYear(self);
#endif
	
    ThenSetMonthAndDayOfMonth(self);
    setDayOfWeek(self);
}


RtcTime * RtcTime_Create(int daysSince1980)
{
     RtcTime * self = calloc(1, sizeof(RtcTime));
     self->daysSince1980 = daysSince1980;
     initRtcTime(self);
     return self;
}

void RtcTime_Destroy(RtcTime * self)
{
    free(self);
}

int RtcTime_GetYear(RtcTime * self)
{
   return self->year;
}

int RtcTime_GetMonth(RtcTime * self)
{
    return self->month;
}

int RtcTime_GetDayOfMonth(RtcTime * self)
{
    return self->dayOfMonth;
}

int RtcTime_GetDayOfWeek(RtcTime * self)
{
    return self->dayOfWeek;
}





#if TEST == 0 

void SetYearAndDayOfYear(RtcTime * time)
{
    int days = time->daysSince1980;
    int year = STARTING_YEAR;
    while (days > 365)
    {
        if (IsLeapYear(year))
        {
            if (days > 366)
            {
                days -= 366;
                year += 1;
            }
        }
        else
        {
            days -= 365;
            year += 1;
        }
    }

    time->dayOfYear = days;
    time->year = year;
}

#elif TEST == 1

void monitorLoop(int days);
void SetYearAndDayOfYear(RtcTime * time)
{
    int days = time->daysSince1980;
    int year = STARTING_YEAR;
    while (days > 365)
    {
        if (IsLeapYear(year))
        {
            if (days > 366)
            {
                days -= 366;
                year += 1;
            }
        }
        else
        {
            days -= 365;
            year += 1;
        }
		
        monitorLoop(days);
    }
    time->dayOfYear = days;
    time->year = year;
}

#else

void FirstSetYearAndDayOfYear(RtcTime * self)
{
    int days = self->daysSince1980;
    int year = STARTING_YEAR;
    int daysInYear = GetDaysInYear(year);

    while (days > daysInYear)
    {
        year++;
        days -= daysInYear;
        daysInYear = GetDaysInYear(year);
    }

    self->dayOfYear = days;
    self->year = year;
}

#endif