#ifndef YC_DATE_JPTK_CALENDAR_H_INCLUDED
#define YC_DATE_JPTK_CALENDAR_H_INCLUDED

namespace yc { namespace date {
    namespace date_time = boost::gregorian::date_time;

    class JPTKCalendar : public Calendar {
    public:
        bool isWeekend(const Date& date) const;
        bool isBusinessDay(const Date& date) const;
    };
    
} } // namespace yc { namespace date {


#endif // #ifndef YC_DATE_JPTK_CALENDAR_H_INCLUDED

