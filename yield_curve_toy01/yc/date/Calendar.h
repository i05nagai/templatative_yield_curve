#ifndef YC_DATE_CALENDAR_H_INCLUDED
#define YC_DATE_CALENDAR_H_INCLUDED

#include "Date.h"

namespace yc { namespace date {
    class Calendar {
    public:
        Date adjust(const Date& date,
                    BusinessDayConvention convention = Following) const;

        Date advance(const Date& date,
                     const int days,
                     BusinessDayConvention convention = Following,
                     bool endOfMonth = false) const;

        virtual bool isHoliday(const Date& date) const = 0;
        virtual bool isBusinessDay(const Date& date) const = 0;
    };
} // namespace yc { namespace date {

#endif // #ifndef YC_DATE_CALENDAR_H_INCLUDED



