#ifndef AD_TEST_EXPRESSION_TEMPLATE_TEST_H_INCLUDED
#define AD_TEST_EXPRESSION_TEMPLATE_TEST_H_INCLUDED

#include "ad/functor.h"

namespace ad_test {
    namespace ublas = boost::numeric::ublas;
    struct H1 {
        typedef ublas::vector<double> value_type;
        typedef double result_type;
        double operator()(const ublas::vector<double>& x)
        {
            return 1.0;
        }
    };
    struct H2 {
        typedef ublas::vector<double> value_type;
        typedef double result_type;
        double operator()(const ublas::vector<double>& x)
        {
            return 4.0;
        }
    };
    bool expression_template_test()
    {
        std::cout << "---------start-------" << std::endl;

        /* expression template */
        ublas::vector<double> v1(10);
        ublas::vector<double> v2(10);
        ublas::vector<double> v3(10);
        for (std::size_t i = 0; i < v1.size(); ++i) {
            v1(i) = i * 0.1;
            v2(i) = i * 0.2;
            v3(i) = i * 0.3;
        }

        {
            ublas::vector<double> v4 = v1 + ad::log(ad::exp(v2)) + (-v3);
            DISPLAY_VECTOR_INFOS(v1);
            DISPLAY_VECTOR_INFOS(v2);
            DISPLAY_VECTOR_INFOS(v3);
            DISPLAY_VECTOR_INFOS(v4);
        }

        {
            H1 h1;
            H2 h2;
            ad::functor2<H1, H2> f(h1, h2);
            ublas::vector<double> x(2);
            ublas::vector<double> y = f(x);
            DISPLAY_VECTOR_INFOS(y);
        }
        std::cout << "---------end--------" << std::endl;

        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_EXPRESSION_TEMPLATE_TEST_H_INCLUDED

