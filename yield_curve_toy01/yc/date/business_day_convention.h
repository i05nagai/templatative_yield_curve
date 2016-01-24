#ifndef YC_DATE_BUSINESS_DAY_CONVENTION_H_INCLUDED
#define YC_DATE_BUSINESS_DAY_CONVENTION_H_INCLUDED

namespace yc { namespace date {
    
    enum BusinessDayConvention {
        //ISDA
        Preceding,                   /*!< Choose the first business
                                          day before the given holiday. */
        Following,                   /*!< Choose the first business day after
                                          the given holiday. */
        ModifiedFollowing,           /*!< Choose the first business day after
                                          the given holiday unless it belongs
                                          to a different month, in which case
                                          choose the first business day before
                                          the holiday. */
        //NON ISDA
        ModifiedPreceding,           /*!< Choose the first business day before
                                          the given holiday unless it belongs
                                          to a different month, in which case
                                          choose the first business day after
                                          the holiday. */
        Unadjusted,                  /*!< Do not adjust. */
        HalfMonthModifiedFollowing,  /*!< Choose the first business day after
                                          the given holiday unless that day
                                          crosses the mid-month (15th) or the
                                          end of month, in which case choose
                                          the first business day before the
                                          holiday. */
        Nearest                      /*!< Choose the nearest business day 
    };
} // namespace yc { namespace date {

#endif // #ifndef YC_DATE_BUSINESS_DAY_CONVENTION_H_INCLUDED
