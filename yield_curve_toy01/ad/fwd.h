#ifndef AD_FWD_H_INCLUDED
#define AD_FWD_H_INCLUDED

namespace ad {

    template <typename E> class vector_expression;

    template <typename T> class dual;

    //exp
    template <typename E> struct exp_traits;
    double exp(const double e);
    template <typename E> dual<E> exp(const dual<E>& e);
    template <typename E>
        typename exp_traits<vector_expression<E> >::result_type 
            exp(const vector_expression<E>& e);

    //log
    template <typename E> struct log_traits;
    double log(const double e);
    template <typename E> dual<E> log(const dual<E>& e);
    template <typename E>
        typename log_traits<vector_expression<E> >::result_type 
            log(const vector_expression<E>& e);
} // namespace ad {

#endif // #ifndef AD_FWD_H_INCLUDED

