#include <cstddef>

#include "helper_macro.h"
#include "vector.h"
#include "dual.h"
#include "function.h"

#include "test/log_test.h"

template <typename T>
struct func_scalar_traits {
private:
    typedef typename T::value_type value_type;
    typedef typename ad::promote_traits<value_type, value_type>::type 
        inner1_value_type;
    typedef inner1_value_type inner2_value_type;
    typedef inner2_value_type inner3_value_type;
        
public:
    typedef ad::dual<inner3_value_type> result_type;
};

//FROM dual<T> TO dual<T>
template <typename T>
typename func_scalar_traits<ad::dual<T> >::result_type 
    func_scalar(const ad::dual<T>& x)
{
    return (x + ad::dual<T>(2.0)) * (x + ad::dual<T>(1.0));
}

//T is ad::Vector<ad::dual<value_type> >
template <typename T>
struct func_vector_traits {
private:
    typedef typename T::value_type value_type;
    typedef ad::vector_binary<
        T, 
        T, 
        ad::scalar_mult<value_type, value_type> > 
            inner_expression1_type;
    typedef typename inner_expression1_type::value_type inner_value_type;
public:
    typedef ad::vector_binary<
        inner_expression1_type, 
        T, 
        ad::scalar_plus<inner_value_type, value_type> > 
            result_type;
};


//FROM vec<dual<T>> TO vec<dual<T>>
template <typename T>
typename func_vector_traits<ad::Vector<T> >::result_type 
    func_vector(const ad::Vector<T>& x)
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
        ad::Vector<double> v4 = v1 + ad::log(ad::exp(v2)) + (-v3);
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
        const func_scalar_traits<ad::dual<double> >::result_type& y 
            = func_scalar(x);
        DISPLAY_VAR(y.v());
        DISPLAY_VAR(y.d());
    }

    {
        std::cout << "ad::exp(x)" << std::endl;
        ad::dual<double> x(3.0, 1.0);
        const func_scalar_traits<ad::dual<double> >::result_type& y 
            = func_scalar(ad::log(ad::exp(x)));
        DISPLAY_VAR(y.v());
        DISPLAY_VAR(y.d());
    }

    //vector: size_1
    {
        typedef ad::dual<double> value_type;
        //typedef double value_type;
        typedef ad::Vector<value_type> domain_type;
        domain_type x(1);
        x(0) = value_type(3.0, 1.0); //bad interface
        //x(0) = value_type(3.0);
        typedef typename func_vector_traits<
            ad::Vector<ad::dual<double> > >::result_type result_type;
        const result_type& y = func_vector(x);
        DISPLAY_VAR(y(0).v());
        DISPLAY_VAR(y(0).d());
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
        typedef typename func_vector_traits<
            ad::Vector<ad::dual<double> > >::result_type result_type;
        const result_type& y = func_vector(x);
        DISPLAY_VAR(y(0).v());
        DISPLAY_VAR(y(0).d());
        DISPLAY_VAR(y(1).v());
        DISPLAY_VAR(y(1).d());
    }

    ad_test::log_test();

    return 0;
}

