#ifndef DDD_AD_FWD_H_INCLUDED
#define DDD_AD_FWD_H_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

namespace ddd { namespace ad {
    namespace ublas = boost::numeric::ublas;

    //template <typename E> class vector_expression;

    template <typename E> class dual_expression;
    template <typename T, typename I> class dual;

    /*
     * exp
     */
    template <typename E> struct exp_traits;
    template <typename E> typename exp_traits<E>::result_type exp(
        const E& e, 
        typename boost::enable_if<boost::is_arithmetic<E> >::type* = NULL);
    //vector
    template <typename E> struct vector_exp_traits;
    //dual
    template <typename E> struct dual_exp_traits;

    /*
     * log
     */
    template <typename E> struct log_traits;
    template <typename E> 
    typename log_traits<E>::result_type log(
        const E& e,
        typename boost::enable_if<boost::is_arithmetic<E> >::type* = NULL);
    //vector
    template <typename E> struct vector_log_traits;
    //dual
    template <typename E> struct dual_log_traits;

    /*
     * type_traits.h
     */

    template <typename T> 
    struct type_traits;

    template<class X, class Y>
    struct promote_traits;

    template <typename T, bool Cond = boost::is_base_of<
        boost::numeric::ublas::vector_expression<T>, T>::value> 
    struct is_vector;

    template <typename T, bool Cond 
        = boost::is_base_of<dual_expression<T>, T>::value> 
    struct is_scalar_dual; 

    template <typename T, bool Cond = is_vector<T>::value>
    struct is_vector_dual; 

    template <typename T, bool Cond = is_scalar_dual<T>::value >
    struct is_dual; 

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_FWD_H_INCLUDED

