#ifndef DD_DATE_DAYCOUNTFRACTION_H_INCLUDED
#define DD_DATE_DAYCOUNTFRACTION_H_INCLUDED

#include "Date.h"

namespace dd { namespace date {
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
} // namespace dd { namespace date {
#endif // #ifndef DD_DATE_DAYCOUNTFRACTION_H_INCLUDED
