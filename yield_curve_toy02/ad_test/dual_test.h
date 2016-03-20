#ifndef AD_TEST_DUAL_TEST_H_INCLUDED
#define AD_TEST_DUAL_TEST_H_INCLUDED

#include "ad/helper_function.h"
#include "ad/helper_macro.h"
#include "ad/dual.h"

namespace ad_test {
    namespace ad = ddd::ad;
    namespace ublas = boost::numeric::ublas;
    bool dual_test() {
        std::cout << "---------start-------" << std::endl;
        std::cout << "---size=0" << std::endl;
        //case: size = 0
        {
            ad::dual<double> c1(1.0);
            ad::dual<double> c2(2.0);
            DISPLAY_DUAL(c1);
            DISPLAY_DUAL(c2);
            ad::dual<double> c3 = c1 + c2;
            ad::dual<double> c4 = c1 - c2;
            ad::dual<double> c5 = c1 * c2;
            ad::dual<double> c6 = c1 / c2;
            ad::dual<double> c0 = c1 + c2 + c1 - c2 + c1 * c2 + c1 / c2;
            std::cout << "c3 = c1 + c2" << std::endl;
            DISPLAY_DUAL(c3);
            std::cout << "c4 = c1 - c2" << std::endl;
            DISPLAY_DUAL(c4);
            std::cout << "c5 = c1 * c2" << std::endl;
            DISPLAY_DUAL(c5);
            std::cout << "c6 = c1 / c2" << std::endl;
            DISPLAY_DUAL(c6);
            std::cout << "c0 = c1 + c2 + c1 - c2 + c1 * c2 + c1 / c2" << std::endl;
            DISPLAY_DUAL(c0);
        }
        std::cout << "---size=1" << std::endl;
        //case: size = 1
        {
           ublas::vector<double> d1(1, 0.0);
           ublas::vector<double> d2(1, 1.0);
           ad::dual<double> c1(1.0, d1);
           ad::dual<double> c2(2.0, d2);
           DISPLAY_DUAL(c1);
           DISPLAY_DUAL(c2);
           ad::dual<double> c3 = c1 + c2;
           ad::dual<double> c4 = c1 - c2;
           ad::dual<double> c5 = c1 * c2;
           ad::dual<double> c6 = c1 / c2;
           ad::dual<double> c0 = c1 + c2 + c1 - c2 + c1 * c2 + c1 / c2;
           std::cout << "c3 = c1 + c2" << std::endl;
           DISPLAY_DUAL(c3);
           std::cout << "c4 = c1 - c2" << std::endl;
           DISPLAY_DUAL(c4);
           std::cout << "c5 = c1 * c2" << std::endl;
           DISPLAY_DUAL(c5);
           std::cout << "c6 = c1 / c2" << std::endl;
           DISPLAY_DUAL(c6);
           std::cout << "c0 = c1 + c2 + c1 - c2 + c1 * c2 + c1 / c2" << std::endl;
           DISPLAY_DUAL(c0);
       }

        //case: size = 2
        {
        }

        //case: dim=2, size=2
        std::cout << "---dim=2, size=2" << std::endl;
        {
            ad::dual<double> c10 = ad::make_variable(1.0, 2, 0);
            ad::dual<double> c11 = ad::make_constant(2.0, 2);
            ad::dual<double> c20 = ad::make_constant(3.0, 2);
            ad::dual<double> c21 = ad::make_variable(4.0, 2, 1);
            ublas::vector<ad::dual<double> > c1(2);
            ublas::vector<ad::dual<double> > c2(2);
            c1(0) = c10;
            c1(1) = c11;
            c2(0) = c20;
            c2(1) = c21;
            DISPLAY_DUAL_MULTI_VAR(c1);
            DISPLAY_DUAL_MULTI_VAR(c2);
            ublas::vector<ad::dual<double> > c3 = c1 + c2;
            ublas::vector<ad::dual<double> > c4 = c1 - c2;
            ublas::vector<ad::dual<double> > c5 = ublas::element_prod(c1, c2);
            ublas::vector<ad::dual<double> > c6 = ublas::element_div(c1, c2);
            ublas::vector<ad::dual<double> > c0 = c1 + c2 + c1 - c2 
                + ublas::element_prod(c1, c2) + ublas::element_div(c1, c2);
            std::cout << "c3 = c1 + c2" << std::endl;
            DISPLAY_DUAL_MULTI_VAR(c3);
            std::cout << "c4 = c1 - c2" << std::endl;
            DISPLAY_DUAL_MULTI_VAR(c4);
            std::cout << "c5 = c1 * c2" << std::endl;
            DISPLAY_DUAL_MULTI_VAR(c5);
            std::cout << "c6 = c1 / c2" << std::endl;
            DISPLAY_DUAL_MULTI_VAR(c6);
            std::cout << "c0 = c1 + c2 + c1 - c2 "
                << "+ ublas::element_prod(c1, c2) "
                << "+ ublas::element_div(c1, c2)" << std::endl;
            DISPLAY_DUAL_MULTI_VAR(c0);
        }

        //case: check operator dual x double
//        std::cout << "---check operator dual x double" << std::endl;
//        {
//            ad::dual<double> c = ad::make_variable(1.0, 2, 0);
//            double v = 2.0;
//            DISPLAY_DUAL(c);
//            DISPLAY_VAR(v);
//            ad::dual<double> c3 = v + c;
//            //DISPLAY_DUAL(c3);
//        }

        std::cout << "---------end---------" << std::endl;
        return true;
    }
} // namespace ad_test {
#endif // #ifndef AD_TEST_DUAL_TEST_H_INCLUDED

