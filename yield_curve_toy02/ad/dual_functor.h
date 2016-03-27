/**
 * @file dual_functor.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-03-27
 */

#ifndef DDD_AD_DUAL_FUNCTOR_H_INCLUDED
#define DDD_AD_DUAL_FUNCTOR_H_INCLUDED

#include <boost/numeric/ublas/functional.hpp>
#include "fwd.h"

namespace ddd { namespace ad {
    /*--------------------------------------------------------------------------
     * value binary functors.
     *-------------------------------------------------------------------------*/
#define DEFINE_DUAL_VALUE_BINARY_FUNCTOR(op_name, op)                       \
    template<typename E1, typename E2>                                      \
    struct value_ ## op_name {                                              \
    private:                                                                \
        /*value*/                                                           \
        typedef typename E1::value_type value1_type;                        \
        typedef typename E2::value_type value2_type;                        \
        /*inf*/                                                             \
        /*functor*/                                                         \
        typedef ublas::scalar_ ## op_name<                                  \
            value1_type,                                                    \
            value2_type> functor_type;                                      \
                                                                            \
    public:                                                                 \
        /*arugument*/                                                       \
        typedef typename E1::const_closure_type argument1_type;             \
        typedef typename E2::const_closure_type argument2_type;             \
        /*result*/                                                          \
        typedef typename functor_type::result_type result_type;             \
                                                                            \
    public:                                                                 \
        static result_type apply(argument1_type e1, argument2_type e2)      \
        {                                                                   \
            return e1.v() op e1.v();                                        \
        }                                                                   \
    };

    DEFINE_DUAL_VALUE_BINARY_FUNCTOR(plus, +);
    DEFINE_DUAL_VALUE_BINARY_FUNCTOR(minus, -);
    DEFINE_DUAL_VALUE_BINARY_FUNCTOR(multiplies, *);
    DEFINE_DUAL_VALUE_BINARY_FUNCTOR(divides, /);

    /*--------------------------------------------------------------------------
     * infinitesimal binary functors.
     *-------------------------------------------------------------------------*/
    //for operator +
    template<typename E1, typename E2>
    struct infinitesimal_plus {
    private:
        typedef infinitesimal_plus_expression_traits<E1, E2> _Tr;
    public:
        //arugument
        typedef typename E1::const_closure_type argument1_type;
        typedef typename E2::const_closure_type argument2_type;
        //expression_type
        typedef typename _Tr::expression_type expression_type;
        //result
        typedef expression_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() + e2.d();
        }
    };

    //for operator -
    template<typename E1, typename E2>
    struct infinitesimal_minus {
    private:
        //value
        //inf
        typedef typename E1::infinitesimal_type infinitesimal1_type;
        typedef typename E2::infinitesimal_type infinitesimal2_type;
        typedef typename infinitesimal1_type::value_type 
            infinitesimal1_value_type;
        typedef typename infinitesimal2_type::value_type 
            infinitesimal2_value_type;
        //expression
        typedef infinitesimal_minus_expression_traits<E1, E2> _Tr;
    public:
        //arugument
        typedef typename E1::const_closure_type argument1_type;
        typedef typename E2::const_closure_type argument2_type;
        //expression_type
        typedef typename _Tr::expression_type expression_type;
        //result_type
        typedef expression_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() - e2.d();
        }
    };

    //for operator *
    template<typename E1, typename E2>
    struct infinitesimal_multiplies {
    private:
        //value
        //inf
        typedef typename E1::infinitesimal_type infinitesimal1_type;
        typedef typename E2::infinitesimal_type infinitesimal2_type;
        typedef typename infinitesimal1_type::value_type 
            infinitesimal1_value_type;
        typedef typename infinitesimal2_type::value_type 
            infinitesimal2_value_type;
        //expression
        typedef infinitesimal_multiplies_expression_traits<E1, E2> _Tr;
    public:
        //arugument
        typedef typename E1::const_closure_type argument1_type;
        typedef typename E2::const_closure_type argument2_type;
        //expression_type
        typedef typename _Tr::expression_type expression_type;
        //result_type
        typedef expression_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() * e2.v() + e1.v() * e2.d();
        }
    };

    //for operator /
    template<typename E1, typename E2>
    struct infinitesimal_divides {
    private:
        //value
        //inf
        typedef typename E1::infinitesimal_type infinitesimal1_type;
        typedef typename E2::infinitesimal_type infinitesimal2_type;
        typedef typename infinitesimal1_type::value_type 
            infinitesimal1_value_type;
        typedef typename infinitesimal2_type::value_type 
            infinitesimal2_value_type;
        //expression
        typedef infinitesimal_divides_expression_traits<E1, E2> _Tr;
    public:
        //arugument
        typedef typename E1::const_closure_type argument1_type;
        typedef typename E2::const_closure_type argument2_type;
        //expression_type
        typedef typename _Tr::expression_type expression_type;
        //result_type
        typedef expression_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return (e1.d() * e2.v() - e1.v() * e2.d()) / (e2.v() * e2.v());
        }
    };

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_DUAL_FUNCTOR_H_INCLUDED
