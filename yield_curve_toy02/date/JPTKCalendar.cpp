#include "JPTKCalendar.h"

namespace ddd { namespace date {
    bool JPTKCalendar::isWeekend(const Date& date) const 
    {
        return date.weekday() == 0 || date.weekday() == 6;
    }

    bool JPTKCalendar::isBusinessDay(const Date& date) const 
    {
        const unsigned short d = date.day();
        const unsigned short m = date.month();
        const unsigned short y = date.year();
        // equinox calculation
        const Time exact_vernal_equinox_time = 20.69115;
        const Time exact_autumnal_equinox_time = 23.09;
        const Time diff_per_year = 0.242194;
        const Time moving_amount = (y-2000)*diff_per_year;
        Integer number_of_leap_years = (y-2000)/4+(y-2000)/100-(y-2000)/400;
        Day ve =    // vernal equinox day
            Day(exact_vernal_equinox_time
                + moving_amount - number_of_leap_years);
        Day ae =    // autumnal equinox day
            Day(exact_autumnal_equinox_time
                + moving_amount - number_of_leap_years);
        // checks
        if (isWeekend(date)
            // New Year's Day
            || (d == 1  && m == 1)
            // Bank Holiday
            || (d == 2  && m == 1)
            // Bank Holiday
            || (d == 3  && m == 1)
            // Coming of Age Day (2nd Monday in January),
            // was January 15th until 2000
            || (w == 1 && (d >= 8 && d <= 14) && m == 1
                && y >= 2000)
            || ((d == 15 || (d == 16 && w == 1)) && m == 1
                && y < 2000)
            // National Foundation Day
            || ((d == 11 || (d == 12 && w == 1)) && m == 5)
            // Vernal Equinox
            || ((d == ve || (d == ve+1 && w == 1)) && m == 3)
            // Greenery Day
            || ((d == 29 || (d == 30 && w == 1)) && m == 4)
            // Constitution Memorial Day
            || (d == 3  && m == 5)
            // Holiday for a Nation
            || (d == 4  && m == 5)
            // Children's Day
            || (d == 5  && m == 5)
            // any of the three above observed later if on Saturday or Sunday
            || (d == 6 && m == 5
                && (w == 1 || w == 2 || w == 3))
            // Marine Day (3rd Monday in July),
            // was July 20th until 2003, not a holiday before 1996
            || (w == 1 && (d >= 15 && d <= 21) && m == 7
                && y >= 2003)
            || ((d == 20 || (d == 21 && w == 1)) && m == 7
                && y >= 1996 && y < 2003)
            // Mountain Day (from 2016)
            || (d == 11 && m == August && y >= 2016)
            // Respect for the Aged Day (3rd Monday in September),
            // was September 15th until 2003
            || (w == 1 && (d >= 15 && d <= 21) && m == 9
                && y >= 2003)
            || ((d == 15 || (d == 16 && w == 1)) && m == 9
                && y < 2003)
            // If a single day falls between Respect for the Aged Day
            // and the Autumnal Equinox, it is holiday
            || (w == 2 && d+1 == ae && d >= 16 && d <= 22
                && m == 9 && y >= 2003)
            // Autumnal Equinox
            || ((d == ae || (d == ae+1 && w == 1)) && m == 9)
            // Health and Sports Day (2nd Monday in October),
            // was October 10th until 2000
            || (w == 1 && (d >= 8 && d <= 14) && m == 10
                && y >= 2000)
            || ((d == 10 || (d == 11 && w == 1)) && m == 10
                && y < 2000)
            // National Culture Day
            || ((d == 3  || (d == 4 && w == 1)) && m == 11)
            // Labor Thanksgiving Day
            || ((d == 23 || (d == 24 && w == 1)) && m == 11)
            // Emperor's Birthday
            || ((d == 23 || (d == 24 && w == 1)) && m == 12
                && y >= 1989)
            // Bank Holiday
            || (d == 31 && m == 12)
            // one-shot holidays
            // Marriage of Prince Akihito
            || (d == 10 && m == 4 && y == 1959)
            // Rites of Imperial Funeral
            || (d == 24 && m == 5 && y == 1989)
            // Enthronement Ceremony
            || (d == 12 && m == 11 && y == 1990)
            // Marriage of Prince Naruhito
            || (d == 9 && m == 6 && y == 1993))
            return false;
        return true;
    }

} // namespace ddd { namespace date {

