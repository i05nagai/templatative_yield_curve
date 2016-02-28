#ifndef DDD_AD_FUNCTOR_H_INCLUDED
#define DDD_AD_FUNCTOR_H_INCLUDED

#include <cmath>
#include "fwd.h"

namespace ddd { namespace ad {
    /*
     * unary functors
     */

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

    /*
     * functors
     */
    // R^n -> R^2
    template <typename F1, typename F2>
    class functor2 {
    private:
        typedef typename F1::value_type value1_type;
        typedef typename F2::value_type value2_type;
        typedef typename F1::result_type result1_type;
        typedef typename F2::result_type result2_type;
    public:
        typedef F1 function1_type;
        typedef F2 function2_type;
        typedef typename promote_traits<
            value1_type, value2_type>::type value_type;
        typedef typename promote_traits<
            result1_type, result2_type>::type result_value_type;
        //TODO: need to consider value_type is scalar(e.g. double)
        typedef typename value_type::value_type element_type;
        typedef ublas::vector<element_type> result_type;
    public:
        functor2(const function1_type& f1, const function2_type& f2)
        : _f1(f1), _f2(f2)
        {
        }

        result_type operator()(
            const value_type& x)
        {
            result_type y(2);
            y[0] = _f1(x);
            y[1] = _f2(x);
            return y;
        }

    private:
        function1_type _f1;
        function2_type _f2;
    };

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_FUNCTOR_H_INCLUDED

