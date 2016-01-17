#ifndef AD_TEST_DUAL_TEST_H_INCLUDED
#define AD_TEST_DUAL_TEST_H_INCLUDED

#include "../helper_macro.h"
#include "../dual.h"

namespace ad_test {
    namespace ublas = boost::numeric::ublas;
    bool dual_test() {
        std::cout << "---------start-------" << std::endl;
        //case: size = 1
        {
            ublas::vector<double> dx(1, 1);
            ublas::vector<double> dz(1, 1);
            ad::dual<double> x(1.0, dx); 
            const double c = 2.0;
            ad::dual<double> z(1.0, dz); 

            //TODO:bad interface
            //w1 = x + 2 - x
            ad::dual<double> w1 = x + c - z;
            DISPLAY_DUAL(w1);

            //TODO:bad interface
            //w2 = x * 2 / x
            ad::dual<double> w2 = x * c / z;
            DISPLAY_DUAL(w2);

            //w3 = x * 2 / x
            ad::dual<double> w3 = ad::exp(x) * c / z;
            DISPLAY_DUAL(w3);

        }
        //case: size = 2
        {
            ublas::vector<double> dx(2, 0.0);
            dx[0] = 1.0;
            ublas::vector<double> dz(2, 0.0);
            dz[1] = 1.0;
            ad::dual<double, 2> x(1.0, dx); 
            const double c = 2.0; 
            ad::dual<double, 2> z(2.0, dz); 

            //TODO:bad interface
            //w1 = x1 + 2 - x2
            ad::dual<double, 2> w1 = x + c - z;
            DISPLAY_DUAL(w1);

            //TODO:bad interface
            //w2 = x1 * 2 / x2
            ad::dual<double, 2> w2 = x * c / z;
            DISPLAY_DUAL(w2);
            
            //w3 = x1 * 2 / x2
            ad::dual<double, 2> w3 = ad::exp(x) * c / z;
            DISPLAY_DUAL(w3);
        }

        std::cout << "---------end---------" << std::endl;
        return true;
    }
} // namespace ad_test {
#endif // #ifndef AD_TEST_DUAL_TEST_H_INCLUDED

