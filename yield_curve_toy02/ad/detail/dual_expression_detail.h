/**
 * @file dual_expression_detail.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-03-27
 */

#ifndef DDD_AD_DUAL_EXPRESSION_DETAIL_H_INCLUDED
#define DDD_AD_DUAL_EXPRESSION_DETAIL_H_INCLUDED

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include "ad/fwd.h"

namespace ddd { namespace ad { namespace detail {
    /*--------------------------------------------------------------------------
     * traits for plus and minus
     *------------------------------------------------------------------------*/
#define DEFINE_DUAL_INFINITESIMAL_BINARY_TRAITS1(op_name)                       \
    /*no implementation*/                                                       \
    template <typename E1, typename E2>                                         \
    struct infinitesimal_vector_ ## op_name ## _vector_traits<E1, E2, false>;   \
                                                                                \
    /*case: I1 = vector, I2 = vector*/                                          \
    /*from E1 x E2 -> expression_type*/                                         \
    template <typename E1, typename E2>                                         \
    struct infinitesimal_vector_ ## op_name ## _vector_traits<E1, E2, true> {   \
    private:                                                                    \
        /*inf*/                                                                 \
        typedef typename E1::infinitesimal_type infinitesimal1_type;            \
        typedef typename E2::infinitesimal_type infinitesimal2_type;            \
        typedef typename infinitesimal1_type::value_type                        \
            infinitesimal1_value_type;                                          \
        typedef typename infinitesimal2_type::value_type                        \
            infinitesimal2_value_type;                                          \
    public:                                                                     \
        /*expression*/                                                          \
        typedef ublas::vector_binary<                                           \
            infinitesimal1_type,                                                \
            infinitesimal2_type,                                                \
            ublas::scalar_ ## op_name <                                         \
                infinitesimal1_value_type,                                      \
                infinitesimal2_value_type> > expression_type;                   \
    };                                                                          \
                                                                                \
    template <typename E1, typename E2>                                         \
    struct infinitesimal_scalar_ ## op_name ## _scalar_traits<E1, E2, false>    \
    : infinitesimal_vector_ ## op_name ## _vector_traits<E1, E2>                \
    {                                                                           \
    };                                                                          \
                                                                                \
    /*case: I1 = scalar, I2 = scalar*/                                          \
    /*fromt E1 x E2 -> expression_type*/                                        \
    template <typename E1, typename E2>                                         \
    struct infinitesimal_scalar_ ## op_name ## _scalar_traits<E1, E2, true> {   \
    private:                                                                    \
        /*value*/                                                               \
        /*inf*/                                                                 \
        typedef typename E1::infinitesimal_type infinitesimal1_type;            \
        typedef typename E2::infinitesimal_type infinitesimal2_type;            \
        /*functor*/                                                             \
        typedef ublas::scalar_ ## op_name <                                     \
            infinitesimal1_type,                                                \
            infinitesimal2_type> functor_type;                                  \
    public:                                                                     \
        typedef typename functor_type::result_type expression_type;             \
    };

    DEFINE_DUAL_INFINITESIMAL_BINARY_TRAITS1(plus);
    DEFINE_DUAL_INFINITESIMAL_BINARY_TRAITS1(minus);
} } } // namespace ddd { namespace ad { namespace detail {


namespace ddd { namespace ad { namespace detail {
    /*--------------------------------------------------------------------------
     * traits for multiplies
     *------------------------------------------------------------------------*/
    //no implementation
    template <typename E1, typename E2>
    struct infinitesimal_vector_multiplies_vector_traits<E1, E2, false>;

    //case: V1 = V2 = scalar, I1 = vector, I2 = vector
    //from E1 x E2 -> expression_type
    template <typename E1, typename E2>
    struct infinitesimal_vector_multiplies_vector_traits<E1, E2, true> {
    private:
        //value
        typedef typename E1::value_type value1_type;
        typedef const value1_type const_value1_type;
        typedef typename E2::value_type value2_type;
        typedef const value2_type const_value2_type;
        //inf
        typedef typename E1::infinitesimal_type infinitesimal1_type;
        typedef typename E2::infinitesimal_type infinitesimal2_type;
        typedef typename infinitesimal1_type::value_type 
            infinitesimal1_value_type;
        typedef typename infinitesimal2_type::value_type 
            infinitesimal2_value_type;
        //e1.d() * e2.v()
        typedef ublas::scalar_multiplies<
            infinitesimal1_value_type, 
            value2_type> functor1_type;
        typedef ublas::vector_binary_scalar2_traits<
            infinitesimal1_type, 
            const_value2_type, 
            functor1_type> _Tr1;
        typedef typename _Tr1::expression_type expression1_type;
        // e1.v() * e2.d()
        typedef ublas::scalar_multiplies<
            value1_type, 
            infinitesimal2_value_type> functor2_type;
        typedef ublas::vector_binary_scalar1_traits<
            const_value1_type, 
            infinitesimal2_type, 
            functor2_type> _Tr2;
        typedef typename _Tr2::expression_type expression2_type;
        // e1.d() * e2.v() + e1.v() * e2.d()
        typedef typename expression1_type::value_type expression1_value_type;
        typedef typename expression2_type::value_type expression2_value_type;
        typedef ublas::scalar_plus<
            expression1_value_type, 
            expression2_value_type> functor3_type;
        typedef ublas::vector_binary_traits<
            expression1_type,
            expression2_type,
            functor3_type> _Tr3;
    public:
        //expression_type
        typedef typename _Tr3::expression_type expression_type;
    };

    template <typename E1, typename E2>
    struct infinitesimal_scalar_multiplies_scalar_traits<E1, E2, false> 
    : infinitesimal_vector_multiplies_vector_traits<E1, E2>
    {
    };

    //case: V1 = V2 = scalar, I1 = scalar, I2 = scalar
    //from E1 x E2 -> expression_type
    template <typename E1, typename E2>
    struct infinitesimal_scalar_multiplies_scalar_traits<E1, E2, true> {
    private:
        //value
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        //inf
        typedef typename E1::infinitesimal_type infinitesimal1_type;
        typedef typename E2::infinitesimal_type infinitesimal2_type;
        // e1.d() * e2.v()
        typedef ublas::scalar_binary_functor<
            infinitesimal1_type, value2_type> _Tr1;
        // e1.v() * e2.d()
        typedef ublas::scalar_binary_functor<
            value1_type, 
            infinitesimal2_type> _Tr2;
        // e1.v() * e2.d() + e1.d() * e2.v()
        typedef typename _Tr1::result_type expression1_type;
        typedef typename _Tr2::result_type expression2_type;
        typedef ublas::scalar_binary_functor<
            expression1_type, 
            expression2_type> _Tr3;
    public:
        typedef typename _Tr3::result_type expression_type;
    };

} } } // namespace ddd { namespace ad { namespace detail {


namespace ddd { namespace ad { namespace detail {
    /*--------------------------------------------------------------------------
     * traits for divides
     *------------------------------------------------------------------------*/
    //no implementation
    template <typename E1, typename E2>
    struct infinitesimal_vector_divides_vector_traits<E1, E2, false>;

    //case: V1 = V2 = scalar, I1 = vector, I2 = vector
    //from E1 x E2 -> expression_type
    template <typename E1, typename E2>
    struct infinitesimal_vector_divides_vector_traits<E1, E2, true> {
    private:
        //value
        typedef typename E1::value_type value1_type;
        typedef const value1_type const_value1_type;
        typedef typename E2::value_type value2_type;
        typedef const value2_type const_value2_type;
        //inf
        typedef typename E1::infinitesimal_type infinitesimal1_type;
        typedef typename E2::infinitesimal_type infinitesimal2_type;
        typedef typename infinitesimal1_type::value_type 
            infinitesimal1_value_type;
        typedef typename infinitesimal2_type::value_type 
            infinitesimal2_value_type;
        //e1.d() * e2.v() = expression1_type
        typedef ublas::scalar_multiplies<
            infinitesimal1_value_type, 
            value2_type> functor1_type;
        typedef ublas::vector_binary_scalar2_traits<
            infinitesimal1_type, 
            const_value2_type, 
            functor1_type> _Tr1;
        typedef typename _Tr1::expression_type expression1_type;
        // e1.v() * e2.d() = expression2_type
        typedef ublas::scalar_multiplies<
            value1_type, 
            infinitesimal2_value_type> functor2_type;
        typedef ublas::vector_binary_scalar1_traits<
            const_value1_type, 
            infinitesimal2_type, 
            functor2_type> _Tr2;
        typedef typename _Tr2::expression_type expression2_type;
        // e1.d() * e2.v() - e1.v() * e2.d() = expression3_type
        typedef typename expression1_type::value_type expression1_value_type;
        typedef typename expression2_type::value_type expression2_value_type;
        typedef ublas::scalar_minus<
            expression1_value_type, 
            expression2_value_type> functor3_type;
        typedef ublas::vector_binary_traits<
            expression1_type,
            expression2_type,
            functor3_type> _Tr3;
        typedef typename _Tr3::expression_type expression3_type;
        typedef typename expression3_type::value_type expression3_value_type;
        // e2.v() * e2.v() = expression4_type
        typedef ublas::scalar_binary_functor<
            value2_type, 
            value2_type> _Tr4;
        typedef typename _Tr4::result_type expression4_type;
        typedef const expression4_type const_expression4_type;
        // (e1.d() * e2.v() - e1.v() * e2.d()) / e2.v() * e2.v() 
        // = expression_type
        typedef ublas::scalar_divides<
            expression3_value_type, 
            expression4_type> functor5_type;
        typedef ublas::vector_binary_scalar2_traits<
            expression3_type, 
            const_expression4_type, 
            functor5_type> _Tr5;
    public:
        //expression_type
        typedef typename _Tr5::expression_type expression_type;
    };

    template <typename E1, typename E2>
    struct infinitesimal_scalar_divides_scalar_traits<E1, E2, false> 
    : infinitesimal_vector_divides_vector_traits<E1, E2>
    {
    };

    //case: V1 = V2 = scalar, I1 = scalar, I2 = scalar
    //from E1 / E2 -> expression_type
    template <typename E1, typename E2>
    struct infinitesimal_scalar_divides_scalar_traits<E1, E2, true> {
    private:
        //value
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        //inf
        typedef typename E1::infinitesimal_type infinitesimal1_type;
        typedef typename E2::infinitesimal_type infinitesimal2_type;
        // e1.d() * e2.v()
        typedef ublas::scalar_binary_functor<
            infinitesimal1_type, 
            value2_type> _Tr1;
        // e1.v() * e2.d()
        typedef ublas::scalar_binary_functor<
            value1_type, 
            infinitesimal2_type> _Tr2;
        // e1.v() * e2.d() - e1.d() * e2.v()
        typedef typename _Tr1::result_type expression1_type;
        typedef typename _Tr2::result_type expression2_type;
        typedef ublas::scalar_binary_functor<
            expression1_type, 
            expression2_type> _Tr3;
        typedef typename _Tr3::result_type expression3_type;
        // e2.v() * e2.v() = expression4_type
        typedef ublas::scalar_binary_functor<
            value2_type, 
            value2_type> _Tr4;
        typedef typename _Tr4::result_type expression4_type;
        // (e1.d() * e2.v() - e1.v() * e2.d()) / e2.v() * e2.v() 
        // = expression_type
        typedef ublas::scalar_binary_functor<
            expression3_type, 
            expression4_type> _Tr5;

    public:
        typedef typename _Tr5::result_type expression_type;
    };

} } } // namespace ddd { namespace ad { namespace detail {

#endif // #ifndef DDD_AD_DUAL_EXPRESSION_DETAIL_H_INCLUDED

