#ifndef DDD_DATE_DAYCOUNTFRACTION_H_INCLUDED
#define DDD_DATE_DAYCOUNTFRACTION_H_INCLUDED

#include "Date.h"

namespace ddd { namespace date {
    class DayCountFraction {
    public:
        DayCountFraction(
            const boost::shared_ptr<DayCounter> dayCounter);
        double apply(
            const Date& start, 
            const Date& end
            const enum DayCountConvention& DayCountConvention);

    private:
        boost::shared_ptr<DayCounter> _dayCounter;
    };
} // namespace ddd { namespace date {
#endif // #ifndef DDD_DATE_DAYCOUNTFRACTION_H_INCLUDED
