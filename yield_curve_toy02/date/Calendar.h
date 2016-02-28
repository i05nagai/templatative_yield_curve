#ifndef DDD_DATE_CALENDAR_H_INCLUDED
#define DDD_DATE_CALENDAR_H_INCLUDED

#include "Date.h"

namespace ddd { namespace date {
    class Calendar {
    public:
        virtual bool isHoliday(const Date& date) const = 0;
        virtual bool isBusinessDay(const Date& date) const = 0;
    };
} // namespace ddd { namespace date {

#endif // #ifndef DDD_DATE_CALENDAR_H_INCLUDED



