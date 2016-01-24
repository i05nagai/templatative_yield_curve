#ifndef YC_DATE_DATE_DATE_H_INCLUDED
#define YC_DATE_DATE_DATE_H_INCLUDED

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/operators.hpp>

namespace yc { namespace date {
        
    namespace gregorian = boost::gregorian;
    class Date : private 
        boost::less_than_comparable<Date>,
        boost::equality_comparable<Date> {
    public:
        Date(
            const std::size_t year,
            const std::size_t month,
            const std::size_t day);

        unsigned short weekday() const;
        unsigned short year() const;
        unsigned short month() const;
        unsigned short day() const;
        bool operator<(const Date& other) const;
        bool operator==(const Date& other) const;
        Date& operator+=(const int days);
        const Date operator +(const int days) const;
        Date& operator-=(const int days);
        const Date operator -(const int days) const;
        int operator -(const Date& other) const;

    private:
        gregorian::date _date;
    };


} } // namespace yc { namespace date {

#endif // #ifndef YC_DATE_DATE_H_INCLUDED

