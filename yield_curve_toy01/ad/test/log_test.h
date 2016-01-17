#ifndef AD_TEST_LOG_TEST_H_INCLUDED
#define AD_TEST_LOG_TEST_H_INCLUDED

#include "../dual.h"
#include "../vector.h"
#include "../helper_macro.h"

namespace ad_test {
    using namespace ad;

    //T is ad::vector<ad::dual<value_type> >
    template <typename T>
    struct func2_vector_traits {
    private:
        typedef typename T::value_type value_type;
    public:
        typedef ad::vector_unary<T, ad::scalar_log<value_type> > result_type;
    };


    //FROM vec<dual<T>> TO vec<dual<T>>
    template <typename T>
    typename func2_vector_traits<ad::vector<T> >::result_type 
        func2_vector(const ad::vector<T>& x)
    {
        return ad::log(x);
    }

    bool log_test()
    {
        std::cout << "---------start-------" << std::endl;
        std::cout << "case: double->double" << std::endl;
        {
            ad::dual<double> x(3.0, 1.0);
            ad::dual<double> y = ad::log(x);
            DISPLAY_VAR(y.v());
            DISPLAY_VAR(y.d());
        }
        std::cout << "case: dual->dual" << std::endl;
        {
            ad::dual<double> x(3.0, 1.0);
            ad::dual<double> y = ad::log(x);
            DISPLAY_VAR(y.v());
            DISPLAY_VAR(y.d());
        }
        std::cout << "case: vec<dual>->vec<dual>" << std::endl;
        {
            typedef ad::dual<double> value_type;
            //typedef double value_type;
            typedef ad::vector<value_type> domain_type;
            domain_type x(2);
            x(0) = value_type(3.0, 1.0); //bad interface
            x(1) = value_type(2.0, 1.0); //bad interface
            typedef typename func2_vector_traits<
                ad::vector<ad::dual<double> > >::result_type result_type;
            const result_type& y = func2_vector(x);
            DISPLAY_VAR(y(0).v());
            DISPLAY_VAR(y(0).d());
            DISPLAY_VAR(y(1).v());
            DISPLAY_VAR(y(1).d());
        }
        std::cout << "---------end--------" << std::endl;
    }

} // namespace ad_test {
#endif // #ifndef LOG_TEST_H_INCLUDED

