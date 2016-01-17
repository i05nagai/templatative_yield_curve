#ifndef AD_FWD_H_INCLUDED
#define AD_FWD_H_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>

namespace ad {

    template <typename E> class vector_expression;

    template <typename T, int N = 1> class dual;

    //exp
    template <typename E> struct exp_traits;
    template <typename E> 
        typename exp_traits<E>::result_type exp(const E& e);

    //log
    template <typename E> struct log_traits;
    template <typename E> 
        typename log_traits<E>::result_type log(const E& e);
} // namespace ad {

#endif // #ifndef AD_FWD_H_INCLUDED

