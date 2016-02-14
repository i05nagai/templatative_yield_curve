#ifndef AD_TEST_AUTOMATIC_DIFFERENTIATION_TEST_H_INCLUDED
#define AD_TEST_AUTOMATIC_DIFFERENTIATION_TEST_H_INCLUDED
namespace ad_test {

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

    //T is ad::vector<ad::dual<value_type> >
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
    typename func_vector_traits<ad::vector<T> >::result_type 
        func_vector(const ad::vector<T>& x)
    {
        return x * x + x;
    }

    bool automatic_differentiation_test {
        std::cout << "---------start-------" << std::endl;

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

        std::cout << "---------end--------" << std::endl;
        return true;
    }
    
} // namespace ad_test {

#endif // #ifndef AD_TEST_AUTOMATIC_DIFFERENTIATION_TEST_H_INCLUDED
