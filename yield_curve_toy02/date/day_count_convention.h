#ifndef DD_DATE_DAY_COUNT_CONVENTION_H_INCLUDED
#define DD_DATE_DAY_COUNT_CONVENTION_H_INCLUDED

namespace dd { namespace date {
    enum DayCountConvention {
        Act/360,
        Act/365,
        Act/365F,
        30/365,
        BUS/252,
    };
} // namespace dd { namespace date {

#endif // #ifndef DD_DATE_DAY_COUNT_CONVENTION_H_INCLUDED
