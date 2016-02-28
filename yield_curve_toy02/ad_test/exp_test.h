#ifndef AD_TEST_EXP_TEST_H_INCLUDED
#define AD_TEST_EXP_TEST_H_INCLUDED

#include "ad/dual.h"
#include "ad/function.h"
#include "ad/vector.h"
#include "ad/helper_macro.h"

namespace ad_test {
    namespace ad = ddd::ad;
    namespace ublas = boost::numeric::ublas;
    bool exp_test() {
        std::cout << "---------start-------" << std::endl;

        //case: double
        {
            const double x = std::log(1.0);
            const double y = ad::exp(x);
            DISPLAY_VAR(y);
        }

        //case: vector<double>(size = 2)
        {
            ublas::vector<double> x(2);
            x(0) = std::log(1.0);
            x(1) = std::log(2.0);
            ublas::vector<double> y = ad::exp(x);
            DISPLAY_VECTOR_INFOS(y);
        }

        //case: dual(size=1)
        {
            const ad::dual<double> x(std::log(1.0));
            const ad::dual<double> y = ad::exp(x);
            DISPLAY_DUAL(y);
        }

        //case: dual(size=2)
        {
            ublas::vector<double> dx(2, 0.0);
            dx(0) = 1.0;
            ublas::vector<double> dz(2, 0.0);
            dz(1) = 1.0;
            const ad::dual<double, 2> x(std::log(1.0));
            const double c = 3.0;
            const ad::dual<double, 2> z(std::log(2.0));
            //w3 = exp(x1) * 2 / x2
            ad::dual<double, 2> w = ad::exp(x) * c / z;
            DISPLAY_DUAL(w);
        }

        std::cout << "---------end---------" << std::endl;
        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_EXP_TEST_H_INCLUDED
