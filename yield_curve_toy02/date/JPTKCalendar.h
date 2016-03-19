#ifndef DDD_DATE_JPTK_CALENDAR_H_INCLUDED
#define DDD_DATE_JPTK_CALENDAR_H_INCLUDED

namespace ddd { namespace date {
    namespace date_time = boost::gregorian::date_time;

    class JPTKCalendar : public Calendar {
    public:
        bool isWeekend(const Date& date) const;
        bool isBusinessDay(const Date& date) const;
    };
    
} } // namespace ddd { namespace date {


#endif // #ifndef DDD_DATE_JPTK_CALENDAR_H_INCLUDED

