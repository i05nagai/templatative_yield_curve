#ifndef DDD_AD_FWD_H_INCLUDED
#define DDD_AD_FWD_H_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

namespace ddd { namespace ad {
    namespace ublas = boost::numeric::ublas;

    //template <typename E> class vector_expression;

    template <typename E> class dual_expression;
    template <typename V, typename I> class dual;

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

    /*
     * jacobian_matrix.h
     */
    //dual jacobian_matrix: 
    template <typename D, bool Cond = is_scalar_dual<D>::value>
    struct dual_jacobian_matrix_traits;

    template <typename D, bool Cond = is_dual<D>::value>
    struct jacobian_matrix_traits;


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

    /*
     * dual_functor.h
     */
    //operator +
    //value part
    template <typename D1, typename D2, bool Cond =
        boost::mpl::and_<
            boost::is_scalar<typename D1::value_type>,
            boost::is_scalar<typename D2::value_type> >::value>
    struct dual_value_scalar_plus_scalar_traits;
    
    template <typename D1, typename D2>
    struct dual_value_plus_traits;

    //inf part
    template <typename D1, typename D2, bool Cond =
        boost::mpl::and_<
            is_vector<typename D1::inf_type>,
            is_vector<typename D2::inf_type> >::value>
    struct dual_inf_vector_plus_vector_traits;

    template <typename D1, typename D2, bool Cond =
        boost::mpl::and_<
            boost::is_scalar<typename D1::inf_type>,
            boost::is_scalar<typename D2::inf_type> >::value>
    struct dual_inf_scalar_plus_scalar_traits;

    template <typename D1, typename D2>
    struct dual_inf_plus_traits;

    //operator *
    //value part
    template <typename D1, typename D2, bool Cond = 
        boost::mpl::and_<
            boost::is_scalar<typename D1::value_type>,
            boost::is_scalar<typename D2::value_type> >::value>
    struct dual_value_scalar_multiplies_scalar_traits;

    template <typename D1, typename D2>
    struct dual_value_multiplies_traits;

    //inf part
    template <typename D1, typename D2, bool Cond =
        boost::mpl::and_<
            is_vector<typename D1::inf_type>,
            is_vector<typename D2::inf_type> >::value>
    struct dual_inf_vector_multiplies_vector_traits;

    template <typename D1, typename D2, bool Cond = 
        boost::mpl::and_<
            boost::is_scalar<typename D1::inf_type>,
            boost::is_scalar<typename D2::inf_type> >::value>
    struct dual_inf_scalar_multiplies_scalar_traits;

    template <typename D1, typename D2>
    struct dual_inf_multiplies_traits;

    //dual part
    template <typename D1, typename D2>
    class dual_multiplies;

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_FWD_H_INCLUDED

