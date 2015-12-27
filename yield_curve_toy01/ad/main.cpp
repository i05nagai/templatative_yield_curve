#include <cstddef>

#include <boost/typeof/typeof.hpp>

#include "helper_macro.h"
#include "vector.h"
#include "dual.h"

//FROM dual<T> TO dual<T>
template <typename T>
inline ad::dual<T> func_scalar(ad::dual<T> x)
{
    return (x + ad::dual<T>(2.0)) * (x + ad::dual<T>(1.0));
}

//FROM vec<dual<T>> TO vec<dual<T>>
template <typename T>
inline ad::Vector<T> func_vector(ad::Vector<T> x)
{
    return x * x + x;
}

int main(int argc, char const* argv[])
{
    /* expression template */
    ad::Vector<double> v1(10);
    ad::Vector<double> v2(10);
    ad::Vector<double> v3(10);
    for (std::size_t i = 0; i < v1.size(); ++i) {
        v1(i) = i * 0.1;
        v2(i) = i * 0.2;
        v3(i) = i * 0.3;
    }

    {
        ad::Vector<double> v4 = v1 + v2 - v3;
        DISPLAY_VECTOR_INFOS(v1);
        DISPLAY_VECTOR_INFOS(v2);
        DISPLAY_VECTOR_INFOS(v3);
        DISPLAY_VECTOR_INFOS(v4);
    }

    //TODO:
    {
        //hold v1+v2-v3 as expressoin.
        //expression_type e =  v1 + v2 - v3;
        //value_type v = e(0);
    }

    /* automatic differentiation */
    //scalar
    {
        ad::dual<double> x(3.0, 1.0);
        const ad::dual<double>& y = func_scalar(x);
        DISPLAY_VAR(y._a);
        DISPLAY_VAR(y._b);
    }

    //vector: size_1
    {
        typedef ad::dual<double> value_type;
        //typedef double value_type;
        typedef ad::Vector<value_type> domain_type;
        domain_type x(1);
        x(0) = value_type(3.0, 1.0); //bad interface
        //x(0) = value_type(3.0);
        const domain_type& y = func_vector(x);
        DISPLAY_VAR(y(0)._a);
        DISPLAY_VAR(y(0)._b);
    }

    //vector: size_1
    {
        typedef ad::dual<double> value_type;
        //typedef double value_type;
        typedef ad::Vector<value_type> domain_type;
        domain_type x(2);
        x(0) = value_type(3.0, 1.0); //bad interface
        x(1) = value_type(2.0, 1.0); //bad interface
        //x(0) = value_type(3.0);
        const domain_type& y = func_vector(x);
        DISPLAY_VAR(y(0)._a);
        DISPLAY_VAR(y(0)._b);
        DISPLAY_VAR(y(1)._a);
        DISPLAY_VAR(y(1)._b);
    }
    
    return 0;
}

