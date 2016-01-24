#include "Date.h"

namespace yc { namespace date {
        
    Date::Date(
        const std::size_t year,
        const std::size_t month,
        const std::size_t day)
    : _date(year, month, day)
    {
    }

    unsigned short Date::weekday() const
    {
        return gregorian::gregorian_calendar::day_of_week(
            _date.year_month_day());
    }

    unsigned short Date::year() const
    {
        return _date.year();
    }

    unsigned short Date::month() const
    {
        return _date.month();
    }

    unsigned short Date::day() const
    {
        return _date.day();
    }

    bool Date::operator <(const Date& other) const
    {
       return _date < other._date;
    }

    bool Date::operator==(const Date& other) const
    {
       return _date == other._date;
    }

    Date& Date::operator+=(const int days)
    {
        _date += gregorian::date_duration(days);
        return *this;
    }

    const Date Date::operator +(const int days) const
    {
        Date date(*this);
        date += days;
        return date;
    }

    Date& Date::operator-=(const int days)
    {
        _date -= gregorian::date_duration(days);
        return *this;
    }

    const Date Date::operator -(const int days) const
    {
        Date date(*this);
        date -= days;
        return date;
    }

    int Date::operator -(const Date& other) const
    {
        return (_date - other._date).days();
    }
    
} } // namespace yc { namespace date {

