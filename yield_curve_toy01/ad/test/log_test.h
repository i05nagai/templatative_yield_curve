#ifndef AD_TEST_LOG_TEST_H_INCLUDED
#define AD_TEST_LOG_TEST_H_INCLUDED

#include "../dual.h"
#include "../vector.h"
#include "../helper_macro.h"

namespace ad_test {
    namespace ublas = boost::numeric::ublas;
    bool log_test()
    {
        std::cout << "---------start-------" << std::endl;

        //case: double
        {
            const double x = std::exp(1.0);
            const double y = ad::log(x);
            DISPLAY_VAR(y);
        }

        //case: vector<double>(size = 2)
        {
            ad::vector<double> x(2);
            x(0) = std::exp(1.0);
            x(1) = std::exp(2.0);
            ad::vector<double> y = ad::log(x);
            DISPLAY_VECTOR_INFOS(y);
        }

        //case: dual(size=1)
        {
            const ad::dual<double> x(std::exp(1.0));
            const ad::dual<double> y = ad::log(x);
            DISPLAY_DUAL(y);
        }

        //case: dual(size=2)
        {
            ublas::vector<double> dx(2, 0.0);
            dx(0) = 1.0;
            ublas::vector<double> dz(2, 0.0);
            dz(1) = 1.0;
            const ad::dual<double, 2> x(std::exp(1.0));
            const double c = 3.0;
            const ad::dual<double, 2> z(std::exp(2.0));
            //w3 = exp(x1) * 2 / x2
            ad::dual<double, 2> w = ad::log(x) * c / z;
            DISPLAY_DUAL(w);
        }
        std::cout << "---------end--------" << std::endl;
    }

} // namespace ad_test {
#endif // #ifndef AD_TEST_LOG_TEST_H_INCLUDED

