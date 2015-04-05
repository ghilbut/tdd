#include "gmock/gmock.h"

//START: monitorLoop
extern "C"
{
#include "RtcTime.h"

static int lastMonitoredDays;
void monitorLoop(int days)
{
    //CHECK(lastMonitoredDays != days);
	ASSERT_TRUE(lastMonitoredDays != days);
    lastMonitoredDays = days;
	
	if (lastMonitoredDays == days) {
		throw NULL;
	}
}
}
//END: monitorLoop

class RtcTime : public ::testing::Test {
	
protected:
    RtcTime* rtcTime;

    //START: monitorLoop_setup
    void SetUp()
    {
        lastMonitoredDays = -1;
    }
    //END: monitorLoop_setup

    void TearDown()
    {
       RtcTime_Destroy(rtcTime);
    }

    void assertDate(int year, int month, int dayOfMonth, int dayOfWeek)
    {
        //LONGS_EQUAL(year, RtcTime_GetYear(rtcTime));
        //LONGS_EQUAL(dayOfMonth, RtcTime_GetDayOfMonth(rtcTime));
        //LONGS_EQUAL(month, RtcTime_GetMonth(rtcTime));
        //LONGS_EQUAL(dayOfWeek, RtcTime_GetDayOfWeek(rtcTime));
		ASSERT_EQ(year, RtcTime_GetYear(rtcTime));
        ASSERT_EQ(dayOfMonth, RtcTime_GetDayOfMonth(rtcTime));
        ASSERT_EQ(month, RtcTime_GetMonth(rtcTime));
        ASSERT_EQ(dayOfWeek, RtcTime_GetDayOfWeek(rtcTime));

    }

    int daysForYear(int year)
    {
        if (IsLeapYear(year))
            return 366;
        else
            return 365;
    }

    int daysSince1980ForYear(int endYear)
    {
        int days = 0;

        for (int year = 1980; year < endYear; year++)
        {
            days += daysForYear(year);
        }
        return days;
    }


};

TEST_F(RtcTime, 1980_1_1)
{
    rtcTime = RtcTime_Create(1);
    assertDate(1980, 1, 1, Tuesday);
}

TEST_F(RtcTime, 1980_1_2)
{
    rtcTime = RtcTime_Create(2);
    assertDate(1980, 1, 2, Wednesday);
}

TEST_F(RtcTime, 1980_1_31)
{
    rtcTime = RtcTime_Create(31);
    assertDate(1980, 1, 31, Thursday);
}

TEST_F(RtcTime, 1980_2_1)
{
    rtcTime = RtcTime_Create(31+1);
    assertDate(1980, 2, 1, Friday);
}

TEST_F(RtcTime, 1980_2_29_leap)
{
    rtcTime = RtcTime_Create(31+28+1);
    assertDate(1980, 2, 29, Friday);
}

TEST_F(RtcTime, 1980_3_1_leap)
{
    rtcTime = RtcTime_Create(31+29+1);
    assertDate(1980, 3, 1, Saturday);
}

TEST_F(RtcTime, 1980_4_1)
{
    rtcTime = RtcTime_Create(31+29+31+1);
    assertDate(1980, 4, 1, Tuesday);
}

TEST_F(RtcTime, 1980_5_1)
{
    rtcTime = RtcTime_Create(31+29+31+30+1);
    assertDate(1980, 5, 1, Thursday);
}

TEST_F(RtcTime, 1980_6_1)
{
    rtcTime = RtcTime_Create(31+29+31+30+31+1);
    assertDate(1980, 6, 1, Sunday);
}

TEST_F(RtcTime, 1981_1_1)
{
    rtcTime = RtcTime_Create(366+1);
    assertDate(1981, 1, 1, Thursday);
}

TEST_F(RtcTime, 2000_1_1)
{
    int yearStart = daysSince1980ForYear(2000);
    rtcTime = RtcTime_Create(yearStart+1);
    assertDate(2000, 1, 1, Saturday);
}

TEST_F(RtcTime, 2000_3_1_leap)
{
    int yearStart = daysSince1980ForYear(2000);
    rtcTime = RtcTime_Create(yearStart+31+29+1);
    assertDate(2000, 3, 1, Wednesday);
}

//START: 2008_12_31_last_day_of_leap_year
TEST_F(RtcTime, 2008_12_31_last_day_of_leap_year)
{
    int yearStart = daysSince1980ForYear(2008);
    rtcTime = RtcTime_Create(yearStart+366);
    assertDate(2008, 12, 31, Wednesday);
}
//END: 2008_12_31_last_day_of_leap_year

TEST_F(RtcTime, 2008_12_31_zune_bug_fails_this_test)
{
    int yearStart = daysSince1980ForYear(2008);
    rtcTime = RtcTime_Create(yearStart+366);
    assertDate(2008, 12, 31, Wednesday);
}


TEST_F(RtcTime, 2100_3_1_not_leap_year)
{
    int yearStart = daysSince1980ForYear(2100);
    rtcTime = RtcTime_Create(yearStart+31+28+1);
    assertDate(2100, 3, 1, Monday);
}