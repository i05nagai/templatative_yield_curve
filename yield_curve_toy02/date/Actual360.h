#ifndef DD_DATE_ACTUAL360_H_INCLUDED
#define DD_DATE_ACTUAL360_H_INCLUDED

#include "DayCounter.h"

namespace dd { namespace date {
    class Actual360 : public DayCounter {
    private:
        double doOperatorParenthesis(
            const Date& start, const Date& end) const;
        DayCounter* doClone() const;
    };
} } // namespace dd { namespace date {

#endif // #ifndef DD_DATE_ACTUAL360_H_INCLUDED
