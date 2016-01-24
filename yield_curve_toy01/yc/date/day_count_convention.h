#ifndef YC_DATE_DAY_COUNT_CONVENTION_H_INCLUDED
#define YC_DATE_DAY_COUNT_CONVENTION_H_INCLUDED

namespace yc { namespace date {
    enum DayCountConvention {
        Act/360,
        Act/365,
        Act/365F,
        30/365,
        BUS/252,
    };
} // namespace yc { namespace date {

#endif // #ifndef YC_DATE_DAY_COUNT_CONVENTION_H_INCLUDED
