#ifndef AD_TEST_DUAL_TEST_H_INCLUDED
#define AD_TEST_DUAL_TEST_H_INCLUDED

#include "ad/helper_macro.h"
#include "ad/dual.h"


template <typename T>
T func1(T x)
{
    return x + x;
}
template <typename T>
T func2(T x)
{
    return x + x - 2.0;
}
template <typename T>
T func3(T x)
{
    return x * x;
}
template <typename T>
T func4(T x)
{
    return x * x * 2.0 + 2.0;
}

template <typename T>
ad::dual<T> g_func1(T x)
{
    return func1(ad::dual<T>(x) + ad::dual<T>::unit_dual(0));
}

template <typename T>
ad::dual<T> g_func2(T x)
{
    return func2(ad::dual<T>(x) + ad::dual<T>::unit_dual(0));
}

template <typename T>
ad::dual<T> g_func3(T x)
{
    return func3(ad::dual<T>(x) + ad::dual<T>::unit_dual(0));
}

template <typename T>
ad::dual<T> g_func4(T x)
{
    return func4(ad::dual<T>(x) + ad::dual<T>::unit_dual(0));
}

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
        }
        //case: size = 2
        {
            ublas::vector<double> dx(2, 0.0);
            dx(0) = 1.0;
            ublas::vector<double> dz(2, 0.0);
            dz(1) = 1.0;
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

