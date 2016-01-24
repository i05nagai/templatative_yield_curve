#include "Calendar.h"

namespace yc { namespace date {
    Date Calendar::adjust(const Date& d,
                          BusinessDayConvention convention) const 
    {
        if (convention == Unadjusted) {
            return d;
        }

        Date d1 = d;
        if (convention == Following 
            || convention == ModifiedFollowing 
            || convention == HalfMonthModifiedFollowing) {
            while (isHoliday(d1)) {
                d1++;
            }
            if (convention == ModifiedFollowing 
                || convention == HalfMonthModifiedFollowing) {
                if (d1.month() != d.month()) {
                    return adjust(d, Preceding);
                }
                if (convention == HalfMonthModifiedFollowing) {
                    if (d.day() <= 15 && d1.day() > 15) {
                        return adjust(d, Preceding);
                    }
                }
            }
        } 
        else if (convention == Preceding 
            || convention == ModifiedPreceding) {
            while (isHoliday(d1)) {
                d1--;
            }
            if (convention == ModifiedPreceding 
                && d1.month() != d.month()) {
                return adjust(d,Following);
            }
        } 
        else if (c == Nearest) {
            Date d2 = d;
            while (isHoliday(d1) && isHoliday(d2)) {
                d1++;
                d2--;
            }
            if (isHoliday(d1)) {
                return d2;
            }
            else {
                return d1;
            }
        } 

        return d1;
    }


    Date advance(const Date& date,
                 const int days,
                 BusinessDayConvention convention = Following,
                 bool endOfMonth = false) const
    {

    }
} // namespace yc { namespace date {
