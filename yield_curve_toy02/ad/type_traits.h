/**
 * @file type_traits.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-03-28
 */

#ifndef DDD_AD_TYPE_TRAITS_H_INCLUDED
#define DDD_AD_TYPE_TRAITS_H_INCLUDED

#include <boost/type_traits/is_base_of.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include "ad/fwd.h"
#include "ad/dual.h"

namespace ddd { namespace ad {

    /*--------------------------------------------------------------------------
     * type_traits
     *------------------------------------------------------------------------*/
    template <typename T>
    struct type_traits {
    private:
        typedef type_traits<T> self_type;
    public:
        typedef T value_type;
        typedef const T& const_reference;
        typedef T& reference;
    };

    /*--------------------------------------------------------------------------
     * promote_traits
     *------------------------------------------------------------------------*/
    //TODO: need to implement.
    template<class X, class Y>
    struct promote_traits {
        typedef X type;
    };

    /*--------------------------------------------------------------------------
     * is_scalar
     *------------------------------------------------------------------------*/
    //TODO: dual<double> is scalar?
    template <typename T> 
    struct is_scalar 
    : boost::mpl::bool_<boost::is_scalar<T>::value> {
    };

    /*--------------------------------------------------------------------------
     * is_vector
     *------------------------------------------------------------------------*/
    template <typename T> 
    struct is_vector : boost::mpl::bool_<
        boost::is_base_of<ublas::vector_expression<T>, T>::value> {
    };

    /*--------------------------------------------------------------------------
     * is_dual
     *------------------------------------------------------------------------*/
    //scalar dual
    template <typename T>
    struct is_scalar_dual 
    : boost::mpl::bool_<boost::is_base_of<dual_expression<T>, T>::value> 
    {
    };

    //vector dual
    template <typename T>
    struct is_vector_dual<T, true> 
    : boost::mpl::bool_<is_scalar_dual<typename T::value_type>::value> {
    };

    template <typename T>
    struct is_vector_dual<T, false> : boost::mpl::bool_<false> {
    };

    //is_dual
    template <typename T>
    struct is_dual : boost::mpl::bool_<
         boost::mpl::or_<
             is_vector_dual<T>, 
             is_scalar_dual<T> >::value> {
    };


} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_TYPE_TRAITS_H_INCLUDED

