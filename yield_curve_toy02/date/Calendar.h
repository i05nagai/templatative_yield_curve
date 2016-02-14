#ifndef DD_DATE_CALENDAR_H_INCLUDED
#define DD_DATE_CALENDAR_H_INCLUDED

#include "Date.h"

namespace dd { namespace date {
    class Calendar {
    public:
        virtual bool isHoliday(const Date& date) const = 0;
        virtual bool isBusinessDay(const Date& date) const = 0;
    };
} // namespace dd { namespace date {

#endif // #ifndef DD_DATE_CALENDAR_H_INCLUDED



