#include "DayCountFraction.h"

namespace ddd { namespace date {

    DayCountFraction::DayCountFraction(
        const boost::shared_ptr<DayCounter> dayCounter)
    : _dayCounter(_dayCounter.clone())
    {
    }

    double DayCountFraction::apply(
        const Date& start, 
        const Date& end)
    {
        return _dayCounter(start, end);
    }

} // namespace ddd { namespace date {
