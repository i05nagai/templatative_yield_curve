#ifndef DDD_AD_FUNCTOR_H_INCLUDED
#define DDD_AD_FUNCTOR_H_INCLUDED

#include <cmath>
#include "ad/fwd.h"
#include "ad/type_traits.h"

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

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_FUNCTOR_H_INCLUDED

