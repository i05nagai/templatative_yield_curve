#ifndef AD_TEST_DUAL_TEST_H_INCLUDED
#define AD_TEST_DUAL_TEST_H_INCLUDED

#include "ad/helper_macro.h"
#include "ad/dual.h"

namespace ad_test {
    namespace ad = ddd::ad;
    namespace ublas = boost::numeric::ublas;
    bool dual_test() {
        std::cout << "---------start-------" << std::endl;
        //case: size = 1
        {
            //const
            ad::dual<double> c1;
            ad::dual<double> c2;
            //ad::dual<double> c3 = c1 + c2;
        }
        //case: size = 2
        {
        }
        /*
        //case: size = 1, twice differential.
        {
            ad::dual<double> x(1.0, 0u); 

            ad::dual<ad::dual<double> > w1 = g_func1(x);
            DISPLAY_DUAL(w1.v());
            DISPLAY_DUAL(w1.d()(0));

            ad::dual<ad::dual<double> > w2 = g_func2(x);
            DISPLAY_DUAL(w2.v());
            DISPLAY_DUAL(w2.d()(0));

            ad::dual<ad::dual<double> > w3 = g_func3(x);
            DISPLAY_DUAL(w3.v());
            DISPLAY_DUAL(w3.d()(0));

            ad::dual<ad::dual<double> > w4 = g_func4(x);
            DISPLAY_DUAL(w4.v());
            DISPLAY_DUAL(w4.d()(0));

        }
        */

        std::cout << "---------end---------" << std::endl;
        return true;
    }
} // namespace ad_test {
#endif // #ifndef AD_TEST_DUAL_TEST_H_INCLUDED

