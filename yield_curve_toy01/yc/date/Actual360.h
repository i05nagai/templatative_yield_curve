#ifndef YC_DATE_ACTUAL360_H_INCLUDED
#define YC_DATE_ACTUAL360_H_INCLUDED

#include "DayCounter.h"

namespace yc { namespace date {
    class Actual360 : public DayCounter {
    private:
        double doOperatorParenthesis(
            const Date& start, const Date& end) const;
        DayCounter* doClone() const;
    };
} // namespace yc { namespace date {

#endif // #ifndef YC_DATE_ACTUAL360_H_INCLUDED
