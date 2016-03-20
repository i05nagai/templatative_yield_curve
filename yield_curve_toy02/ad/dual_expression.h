#ifndef DDD_AD_DUAL_EXPRESSION_H_INCLUDED
#define DDD_AD_DUAL_EXPRESSION_H_INCLUDED

#include <boost/numeric/ublas/vector_expression.hpp>
#include "ad/dual_functor.h"
#include "ad/detail/dual_expression_detail.h"


namespace ddd { namespace ad {
    namespace ublas = boost::numeric::ublas;

    template <typename E> 
    class dual_expression {
    public:
        typedef E expression_type;
        typedef typename type_traits<expression_type>::const_reference 
            const_reference;
    public:
        const_reference operator()() const 
        {
            return static_cast<const expression_type&>(*this);
        }
    };

    template<typename E1, typename E2, typename VF, typename IF>
    class dual_binary: public dual_expression<dual_binary<E1, E2, VF, IF> > {
        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef VF value_functor_type;
        typedef IF infinitesimal_functor_type;
        typedef typename E1::const_closure_type expression1_closure_type;
        typedef typename E2::const_closure_type expression2_closure_type;
        typedef dual_binary<E1, E2, VF, IF> self_type;
    public:
        //value
        typedef typename value_functor_type::result_type 
            value_type;
        typedef value_type const_value_reference;
        typedef const_value_reference value_reference;
        //infinitesimal
        typedef typename infinitesimal_functor_type::result_type 
            infinitesimal_type;
        typedef infinitesimal_type const_infinitesimal_reference;
        typedef const_infinitesimal_reference infinitesimal_reference;
        //closure
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;

        // Construction and destruction
        dual_binary(const expression1_type& e1, const expression2_type& e2)
        : _e1(e1), _e2(e2)
        {
        }

    public:
        // Element access
        const_value_reference v() const 
        {
            return value_functor_type::apply(_e1, _e2);
        }

        const_infinitesimal_reference d() const 
        {
            return infinitesimal_functor_type::apply(_e1, _e2);
        }

    private:
        expression1_closure_type _e1;
        expression2_closure_type _e2;
    };

    //E1 + E2 -> expression_type of E1 + E2
    template <typename E1, typename E2>
    struct infinitesimal_plus_expression_traits 
    : detail::infinitesimal_scalar_plus_scalar_traits<E1, E2> {
    };


    //E1 - E2 -> expression_type of E1 - E2
    template <typename E1, typename E2>
    struct infinitesimal_minus_expression_traits 
    : detail::infinitesimal_scalar_minus_scalar_traits<E1, E2> {
    };

    //E1 * E2 -> expression_type of E1 * E2
    template <typename E1, typename E2>
    struct infinitesimal_multiplies_expression_traits 
    : detail::infinitesimal_scalar_multiplies_scalar_traits<E1, E2> {
    };

    //E1 / E2 -> expression_type of E1 / E2
    template <typename E1, typename E2>
    struct infinitesimal_divides_expression_traits 
    : detail::infinitesimal_scalar_divides_scalar_traits<E1, E2> {
    };


    template<typename E1, typename E2, typename VF, typename IF>
    struct dual_binary_traits {
        typedef dual_binary<E1, E2, VF, IF> expression_type;
        typedef expression_type result_type; 
    };

    /*
     * dual binary operators
     */
#define DEFINE_DUAL_BINARY_OPERATOR(op_name,op)                                     \
    template<typename E1, typename E2>                                              \
    typename dual_binary_traits<                                                    \
        E1,                                                                         \
        E2,                                                                         \
        value_ ## op_name <E1, E2>,                                                 \
        infinitesimal_ ## op_name <E1, E2> >::result_type                           \
    operator op(                                                                    \
        const dual_expression<E1> &e1,                                              \
        const dual_expression<E2> &e2)                                              \
    {                                                                               \
        typedef typename dual_binary_traits<                                        \
            E1, E2,                                                                 \
            value_ ## op_name <E1, E2>,                                             \
            infinitesimal_ ## op_name <E1, E2> >::expression_type expression_type;  \
        return expression_type(e1(), e2());                                         \
    }

    DEFINE_DUAL_BINARY_OPERATOR(plus, +);
    DEFINE_DUAL_BINARY_OPERATOR(minus, -);
    DEFINE_DUAL_BINARY_OPERATOR(multiplies, *);
    DEFINE_DUAL_BINARY_OPERATOR(divides, /);
    
} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_DUAL_EXPRESSION_H_INCLUDED

