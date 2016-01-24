#include "DayCounter.h"

namespace yc { namespace date {
    double DayCounter::operator()(const Date& start, const Date& end) const
    {
        return this->doOperatorParenthesis();
    }

    boost::shared_ptr<DayCounter> DayCounter::clone() const
    { 
        return boost::shared_ptr<DayCounter>(this->doClone());
    }

} // namespace yc { namespace date {

