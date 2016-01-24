#ifndef YC_DATE_DAYCOUNTFRACTION_H_INCLUDED
#define YC_DATE_DAYCOUNTFRACTION_H_INCLUDED

#include "Date.h"

namespace yc { namespace date {
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
} // namespace yc { namespace date {
#endif // #ifndef YC_DATE_DAYCOUNTFRACTION_H_INCLUDED
