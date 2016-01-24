#ifndef YC_TEST_DATE_DATE_TEST_H_INCLUDED
#define YC_TEST_DATE_DATE_TEST_H_INCLUDED

#include "yc/date/Date.h"

#include <iostream>

namespace yc_test { namespace date {
    inline std::ostream& operator<<(std::ostream& out, const yc::date::Date& d) {
        return out << d.year() << "-" << d.month() << "-" << d.day();
    }

        
    bool DateTest()
    {
        yc::date::Date date1(2015, 4, 30);
        yc::date::Date date2(2015, 10, 31);

        assert(date1 < date2);
        assert(!(date1 >= date2));
        assert(date1 <= date2);
        assert(!(date1 > date2));
        assert(!(date1 == date2));
        assert(date1 != date2);

        int days = date2 - date1;
        std::cout << "days:" << days << std::endl;

        yc::date::Date date3 = date1 + days;
        std::cout << date3 << std::endl;
        yc::date::Date date4 = date2 - days;
        std::cout << date4 << std::endl;

        return true;
    }
    
} } // namespace yc_test { namespace date {

#endif // #ifndef YC_TEST_DATE_TEST_H_INCLUDED

