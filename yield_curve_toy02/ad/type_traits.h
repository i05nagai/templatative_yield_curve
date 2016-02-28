#ifndef DDD_AD_TYPE_TRAITS_H_INCLUDED
#define DDD_AD_TYPE_TRAITS_H_INCLUDED

#include <boost/type_traits/is_base_of.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

#include "ad/fwd.h"
#include "ad/dual.h"

namespace ddd { namespace ad {
    // default traits
    template <typename T>
    struct type_traits {
    private:
        typedef type_traits<T> self_type;
    public:
        typedef T value_type;
        typedef const T& const_reference;
        typedef T& reference;
    };

    //TODO: need to implement.
    template <typename T1, typename T2>
    struct promote_traits {
        typedef T1 type;
    };

    /*
     * is_vector
     */
    template <typename T, bool Cond = boost::is_base_of<
        boost::numeric::ublas::vector_expression<T>, T>::value> 
    struct is_vector;

    template <typename T> 
    struct is_vector<T, false> {
        typedef T type;
        static const bool value = false;
    };

    template <typename T>
    struct is_vector<T, true> {
        typedef T type;
        static const bool value = true;
    };

    /*
     * is_dual
     */
    //scalar dual
    template <typename T, bool Cond 
        = boost::is_base_of<dual_expression<T>, T>::value> 
    struct is_scalar_dual; 

    template <typename T>
    struct is_scalar_dual<T, false> {
        typedef T type;
        static const bool value = false;
    };

    template <typename T> 
    struct is_scalar_dual<T, true> {
        typedef T type;
        static const bool value = true;
    };

    //vector dual
    template <typename T, bool Cond = is_vector<T>::value>
    struct is_vector_dual; 

    template <typename T>
    struct is_vector_dual<T, false> {
        typedef T type;
        static const bool value = false;
    };

    template <typename T> 
    struct is_vector_dual<T, true> : is_scalar_dual<typename T::value_type> {
    };

    //is_dual
    template <typename T, bool Cond = is_scalar_dual<T>::value >
    struct is_dual; 

    template <typename T>
    struct is_dual<T, false> : is_vector_dual<T> {
    };

    template <typename T> 
    struct is_dual<T, true> {
        typedef T type;
        static const bool value = true;
    };



} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_TYPE_TRAITS_H_INCLUDED

