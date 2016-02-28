#ifndef DDD_DATE_DATE_TIME_H_INCLUDED
#define DDD_DATE_DATE_TIME_H_INCLUDED

namespace ddd { namespace date {
    Date adjust(const Date& date,
        BusinessDayConvention convention) 
    {
        if (convention == Unadjusted) {
            return date;
        }

        Date d1 = date;
        if (convention == Following 
            || convention == ModifiedFollowing 
            || convention == HalfMonthModifiedFollowing) {
            while (isHoliday(d1)) {
                d1++;
            }
            if (convention == ModifiedFollowing 
                || convention == HalfMonthModifiedFollowing) {
                if (d1.month() != d.month()) {
                    return adjust(date, Preceding);
                }
                if (convention == HalfMonthModifiedFollowing) {
                    if (date.day() <= 15 && d1.day() > 15) {
                        return adjust(date, Preceding);
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
                && d1.month() != date.month()) {
                return adjust(date, Following);
            }
        } 
        else if (c == Nearest) {
            Date d2 = date;
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

    Date advance(
        const Date& date,
        const int days,
        BusinessCenter businessCenter,
        BusinessDayConvention convention = Following,
        bool endOfMonth = false) 
    {
        if (days == 0) {
            return adjust(date, c);
        }

        Date d1 = date;
        if (days > 0) {
            while (days > 0) {
                ++d1;
                while (isHoliday(d1)) {
                    ++d1;
                }
                --days;
            }
        } 
        else {
            while (days < 0) {
                d1--;
                while(isHoliday(d1)) {
                    d1--;
                }
                days++;
            }
        }
        return d1;
    }

    
} // namespace ddd { namespace date {

#endif // #ifndef DDD_DATE_DATE_TIME_H_INCLUDED
