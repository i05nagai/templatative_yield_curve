#ifndef AD_FWD_H_INCLUDED
#define AD_FWD_H_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

namespace ad {
    namespace ublas = boost::numeric::ublas;

    //template <typename E> class vector_expression;

    template <typename E> class dual_expression;
    template <typename T, int N = 1> class dual;

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
} // namespace ad {

#endif // #ifndef AD_FWD_H_INCLUDED

