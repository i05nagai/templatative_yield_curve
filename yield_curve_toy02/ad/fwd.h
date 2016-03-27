/**
 * @file fwd.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-03-27
 */

#ifndef DDD_AD_FWD_H_INCLUDED
#define DDD_AD_FWD_H_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

namespace ddd { namespace ad {
    namespace ublas = boost::numeric::ublas;

    /*--------------------------------------------------------------------------
     * dual_function.h
     *-------------------------------------------------------------------------*/
    template <typename E> class dual_expression;
    template <typename V, typename I> class dual;

    //exp
    template <typename E> struct exp_traits;

    template <typename E> 
    typename exp_traits<E>::result_type 
    exp(
        const E& e, 
        typename boost::enable_if<boost::is_arithmetic<E> >::type* = NULL);
    //vector
    template <typename E> struct vector_exp_traits;
    //dual
    template <typename E> struct dual_exp_traits;

    //log
    template <typename E> struct log_traits;

    template <typename E> 
    typename log_traits<E>::result_type 
    log(
        const E& e,
        typename boost::enable_if<boost::is_arithmetic<E> >::type* = NULL);
    //vector
    template <typename E> struct vector_log_traits;
    //dual
    template <typename E> struct dual_log_traits;

    /*--------------------------------------------------------------------------
     * type_traits.h
     *------------------------------------------------------------------------*/
    template <typename T> 
    struct type_traits;

    template<class X, class Y>
    struct promote_traits;

    template <typename T>
    struct is_scalar;

    template <typename T>
    struct is_vector;

    template <typename T>
    struct is_scalar_dual;

    template <typename T, bool Cond = is_vector<T>::value>
    struct is_vector_dual; 

    template <typename T>
    struct is_dual; 

    /*--------------------------------------------------------------------------
     * dual_functor_detail.h
     *------------------------------------------------------------------------*/
    namespace detail {
        //plus
        template <typename E1, typename E2, bool Condition = 
            boost::mpl::and_<
                is_vector<typename E1::infinitesimal_type>,
                is_vector<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_vector_plus_vector_traits;

        template <typename E1, typename E2, bool Condition = 
            boost::mpl::and_<
                boost::is_scalar<typename E1::infinitesimal_type>,
                boost::is_scalar<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_scalar_plus_scalar_traits;

        //minus
        template <typename E1, typename E2, bool Condition = 
            boost::mpl::and_<
                is_vector<typename E1::infinitesimal_type>,
                is_vector<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_vector_minus_vector_traits;

        template <typename E1, typename E2, bool Condition = 
            boost::mpl::and_<
                boost::is_scalar<typename E1::infinitesimal_type>,
                boost::is_scalar<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_scalar_minus_scalar_traits;


        //multiplies
        template <typename E1, typename E2, bool Condition =
            boost::mpl::and_<
                is_vector<typename E1::infinitesimal_type>,
                is_vector<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_vector_multiplies_vector_traits;

        template <typename E1, typename E2, bool Condition = 
            boost::mpl::and_<
                boost::is_scalar<typename E1::infinitesimal_type>,
                boost::is_scalar<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_scalar_multiplies_scalar_traits;

        //divides
        template <typename E1, typename E2, bool Condition = 
            boost::mpl::and_<
                is_vector<typename E1::infinitesimal_type>,
                is_vector<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_vector_divides_vector_traits;

        template <typename E1, typename E2, bool Condition = 
            boost::mpl::and_<
                boost::is_scalar<typename E1::infinitesimal_type>,
                boost::is_scalar<typename E2::infinitesimal_type> >::value
        >
        struct infinitesimal_scalar_divides_scalar_traits;
        
    } // namespace detail


    /*--------------------------------------------------------------------------
     * dual_expression.h
     *-------------------------------------------------------------------------*/
    //E1 + E2 -> expression_type of E1 + E2
    template <typename E1, typename E2>
    struct infinitesimal_plus_expression_traits;

    //E1 - E2 -> expression_type of E1 - E2
    template <typename E1, typename E2>
    struct infinitesimal_minus_expression_traits;

    //E1 * E2 -> expression_type of E1 * E2
    template <typename E1, typename E2>
    struct infinitesimal_multiplies_expression_traits;

    //E1 / E2 -> expression_type of E1 / E2
    template <typename E1, typename E2>
    struct infinitesimal_divides_expression_traits;

    /*--------------------------------------------------------------------------
     * dual_functor.h
     *------------------------------------------------------------------------*/
    //value binary functors.
    template<typename E1, typename E2>
    struct value_plus;

    template<typename E1, typename E2>
    struct value_minus;

    template<typename E1, typename E2>
    struct value_multiplies;

    template<typename E1, typename E2>
    struct value_divides;
    

    //infinitesimal binary functors.
    template<typename E1, typename E2>
    struct infinitesimal_plus;

    template<typename E1, typename E2>
    struct infinitesimal_minus;

    template<typename E1, typename E2>
    struct infinitesimal_multiplies;

    template<typename E1, typename E2>
    struct infinitesimal_divides;

    /*--------------------------------------------------------------------------
     * jacobian_matrix.h
     *------------------------------------------------------------------------*/
    namespace detail {
        
        template <typename D, bool Condition 
            = is_vector<typename D::value_type::infinitesimal_type>::value>
        class jacobian_matrix_adapter_vector_dual;

        template <typename D, bool Condition 
            = is_vector<typename D::infinitesimal_type>::value>
        class jacobian_matrix_adapter_scalar_dual;

        template <typename D, bool Condition = is_vector_dual<D>::value>
        class jacobian_matrix_adapter_impl;
    } // namespace detail

    template <typename D>
    class dual_jacobian_matrix_adapter;

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_FWD_H_INCLUDED

