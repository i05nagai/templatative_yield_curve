#ifndef DDD_DATE_DAY_COUNT_CONVENTION_H_INCLUDED
#define DDD_DATE_DAY_COUNT_CONVENTION_H_INCLUDED

namespace ddd { namespace date {
    enum DayCountConvention {
        Act/360,
        Act/365,
        Act/365F,
        30/365,
        BUS/252,
    };
} // namespace ddd { namespace date {

#endif // #ifndef DDD_DATE_DAY_COUNT_CONVENTION_H_INCLUDED
