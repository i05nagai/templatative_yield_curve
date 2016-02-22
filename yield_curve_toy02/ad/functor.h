#ifndef AD_FUNCTOR_H_INCLUDED
#define AD_FUNCTOR_H_INCLUDED

#include <cmath>
#include "fwd.h"

namespace ad {
    /*
     * unary functors
     */
    template <typename T>
    class unary_minus {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(argument_type v)
        {
            return -v;
        }
    };

    //T is matrix -> inverse matrix
    //T is vector -> inverse matrix which interprets vector as matrix
    //T is scalar -> inverse matrix which interprets scalar as matrix
    template <typename T>
    class unary_invert {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(argument_type v)
        {
            return invert(v);
        }
    };

    template <typename T>
    class scalar_exp {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(argument_type v)
        {
            return ad::exp(v);
        }
    };

    template <typename T>
    class scalar_log {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(argument_type v)
        {
            return ad::log(v);
        }
    };

    /*
     * binary functors
     */
    template <typename T1, typename T2>
    class scalar_plus {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 + v2;
        }
    };

    template <typename T1, typename T2>
    class scalar_minus {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 - v2;
        }
    };

    template<typename T1, typename T2>
    class scalar_mult {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 * v2;
        }
    };

    template<typename T1, typename T2>
    class scalar_div {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            //TODO:need to check zero division.
            return v1 / v2;
        }
    };

    /*
     *
     */
    //(f1, f2,.., fn)(v) -> (f1(v), ..., fn(v))
    template <typename T>
    class unary_vector_functor {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(argument_type v)
        {
            return v;
        }
    };

    // vector -> vector
    template <typename F1, typename F2>
    struct functor2 {
    private:
        typedef typename F1::value_type value1_type;
        typedef typename F2::value_type value2_type;
        typedef typename F1::result_type result1_type;
        typedef typename F2::result_type result2_type;
    public:
        typedef F1 function1_type;
        typedef F2 function2_type;
        typedef typename ad::promote_traits<
            value1_type, value2_type>::type value_type;
        typedef typename ad::promote_traits<
            result1_type, result2_type>::type result_value_type;
        typedef typename ublas::vector<result_value_type> result_type;
    public:
        functor2(const function1_type& f1, const function2_type& f2)
        : _f1(f1), _f2(f2)
        {
        }

        result_type operator()(
            const value_type& x)
        {
            return result_type(_f1(x), _f2(x));
        }

    private:
        function1_type _f1;
        function2_type _f2;
    };

} // namespace ad {

#endif // #ifndef AD_FUNCTOR_H_INCLUDED

