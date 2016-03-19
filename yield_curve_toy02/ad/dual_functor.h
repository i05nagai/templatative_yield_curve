#ifndef DDD_AD_DUAL_FUNCTOR_H_INCLUDED
#define DDD_AD_DUAL_FUNCTOR_H_INCLUDED

#include "fwd.h"
#include <boost/numeric/ublas/functional.hpp>

namespace ddd { namespace ad {
    /*
    operator +
     we assumes type of value is always scalar.
    */
    //value part
    template <typename D1, typename D2>
    struct dual_value_scalar_plus_scalar_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef typename D2::value_type value2_type;
        typedef ublas::scalar_binary_functor<value1_type, value2_type> _Tr;
    public:
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.v() + e2.v();
        }
    };

    template <typename D1, typename D2>
    struct dual_value_plus_traits 
    : dual_value_scalar_plus_scalar_traits<D1, D2> {
    private:
    public:
    };

    //inf part
    template <typename D1, typename D2>
    struct dual_inf_vector_plus_vector_traits<D1, D2, true> {
    private:
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename inf1_type::value_type inf1_value_type;
        typedef typename D2::inf_type inf2_type;
        typedef typename inf2_type::value_type inf2_value_type;
        //
        typedef ublas::scalar_plus<inf1_value_type, inf2_value_type> functor_type;
        typedef ublas::vector_binary_traits<inf1_type, inf2_type, functor_type> _Tr;
    public:
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
        typedef typename _Tr::expression_type expression_type;
    public:
        //dual x dual -> dual.d + dual.d
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() + e2.d();
        }
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_plus_scalar_traits<D1, D2, false> 
    : public dual_inf_vector_plus_vector_traits<D1, D2> {
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_plus_scalar_traits<D1, D2, true> {
    private:
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename D2::inf_type inf2_type;
        typedef ublas::scalar_binary_functor<inf1_type, inf2_type> _Tr;
    public:
        //
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
    public:
        //dual x dual -> dual.d + dual.d
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() + e2.d();
        }
    };
    
    template <typename D1, typename D2>
    struct dual_inf_plus_traits 
    : public dual_inf_scalar_plus_scalar_traits<D1, D2> {
    };

    //dual plus
    template <typename D1, typename D2>
    class dual_plus {
    private:
        //value
        typedef dual_value_plus_traits<D1, D2> _VTr;
        //inf
        typedef dual_inf_plus_traits<D1, D2> _ITr;
    public:
        typedef _VTr value_traits;
        typedef _ITr inf_traits;
    };

    /*
    operator -
     we assumes type of value is always scalar.
    */
    //value part
    template <typename D1, typename D2>
    struct dual_value_scalar_minus_scalar_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef typename D2::value_type value2_type;
        typedef ublas::scalar_binary_functor<value1_type, value2_type> _Tr;
    public:
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.v() - e2.v();
        }
    };

    template <typename D1, typename D2>
    struct dual_value_minus_traits 
    : dual_value_scalar_minus_scalar_traits<D1, D2> {
    private:
    public:
    };

    //inf part
    template <typename D1, typename D2>
    struct dual_inf_vector_minus_vector_traits<D1, D2, true> {
    private:
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename inf1_type::value_type inf1_value_type;
        typedef typename D2::inf_type inf2_type;
        typedef typename inf2_type::value_type inf2_value_type;
        typedef ublas::scalar_minus<inf1_value_type, inf2_value_type> functor_type;
        typedef ublas::vector_binary_traits<inf1_type, inf2_type, functor_type> _Tr;
    public:
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
        typedef typename _Tr::expression_type expression_type;
    public:
        //dual x dual -> dual.d - dual.d
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() - e2.d();
        }
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_minus_scalar_traits<D1, D2, false> 
    : public dual_inf_vector_minus_vector_traits<D1, D2> {
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_minus_scalar_traits<D1, D2, true> {
    private:
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename D2::inf_type inf2_type;
        typedef ublas::scalar_binary_functor<inf1_type, inf2_type> _Tr;
    public:
        //
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
    public:
        //dual x dual -> dual.d + dual.d
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() - e2.d();
        }
    };

    template <typename D1, typename D2>
    struct dual_inf_minus_traits 
    : public dual_inf_scalar_minus_scalar_traits<D1, D2> {
    };

    //dual minus
    template <typename D1, typename D2>
    class dual_minus {
    private:
        //value
        typedef dual_value_minus_traits<D1, D2> _VTr;
        //inf
        typedef dual_inf_minus_traits<D1, D2> _ITr;
    public:
        typedef _VTr value_traits;
        typedef _ITr inf_traits;
    };

    /*
     * operator *
     we assumes type of value is always scalar.
     */
    //value part
    template <typename D1, typename D2>
    struct dual_value_scalar_multiplies_scalar_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef typename D2::value_type value2_type;
        typedef ublas::scalar_binary_functor<value1_type, value2_type> _Tr;
    public:
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.v() * e2.v();
        }
    };

    template <typename D1, typename D2>
    struct dual_value_multiplies_traits 
    : dual_value_scalar_multiplies_scalar_traits<D1, D2> {
    private:
    public:
    };

    //inf part
    template <typename D1, typename D2>
    struct dual_inf_vector_multiplies_vector_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef const value1_type const_value1_type;
        typedef typename D2::value_type value2_type;
        typedef const value2_type const_value2_type;
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename inf1_type::value_type inf1_value_type;
        typedef typename D2::inf_type inf2_type;
        typedef typename inf2_type::value_type inf2_value_type;
        // e1.d() * e2.v()
        typedef ublas::scalar_multiplies<inf1_value_type, value2_type> functor1_type;
        typedef ublas::vector_binary_scalar2_traits<
            inf1_type, 
            const_value2_type, 
            functor1_type> _Tr1;
        typedef typename _Tr1::expression_type expression1_type;
        // e1.v() * e2.d()
        typedef ublas::scalar_multiplies<value1_type, inf2_value_type> functor2_type;
        typedef ublas::vector_binary_scalar1_traits<
            const_value1_type, 
            inf2_type, 
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
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr3::result_type result_type;
        typedef typename _Tr3::expression_type expression_type;
    public:
        //d1 x d2 -> d1.d * d2.v + d1.v * d2.d
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() * e2.v() + e1.v() * e2.d();
        }
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_multiplies_scalar_traits<D1, D2, false> 
    : public dual_inf_vector_multiplies_vector_traits<D1, D2> {
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_multiplies_scalar_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef typename D2::value_type value2_type;
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename D2::inf_type inf2_type;
        // e1.d() * e2.v()
        typedef ublas::scalar_binary_functor<inf1_type, value2_type> _Tr1;
        // e1.v() * e2.d()
        typedef ublas::scalar_binary_functor<value1_type, inf2_type> _Tr2;
        // e1.v() * e2.d() + e1.d() * e2.v()
        typedef typename _Tr1::result_type expression1_type;
        typedef typename _Tr2::result_type expression2_type;
        typedef ublas::scalar_binary_functor<
            expression1_type, 
            expression2_type> _Tr3;
    public:
        //
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr3::result_type result_type;
    public:
        //dual x dual -> dual.v * dual.d + dual.d * dual.v
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.d() * e2.v() + e1.v() * e2.d();
        }
    };

    template <typename D1, typename D2>
    struct dual_inf_multiplies_traits 
    : public dual_inf_scalar_multiplies_scalar_traits<D1, D2> {
    };

    //dual part
    template <typename D1, typename D2>
    class dual_multiplies {
    private:
        //value
        typedef dual_value_multiplies_traits<D1, D2> _VTr;
        //inf
        typedef dual_inf_multiplies_traits<D1, D2> _ITr;
    public:
        typedef _VTr value_traits;
        typedef _ITr inf_traits;
    };

    /*
    operator /
     we assumes type of value is always scalar.
    */
    //value part
    template <typename D1, typename D2>
    struct dual_value_scalar_divides_scalar_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef typename D2::value_type value2_type;
        typedef ublas::scalar_binary_functor<value1_type, value2_type> _Tr;
    public:
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr::result_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            //TODO:check zero division.
            return e1.v() / e2.v();
        }
    };

    template <typename D1, typename D2>
    struct dual_value_divides_traits 
    : dual_value_scalar_divides_scalar_traits<D1, D2> {
    private:
    public:
    };

    //inf part
    template <typename D1, typename D2>
    struct dual_inf_vector_divides_vector_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef const value1_type const_value1_type;
        typedef typename D2::value_type value2_type;
        typedef const value2_type const_value2_type;
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename inf1_type::value_type inf1_value_type;
        typedef typename D2::inf_type inf2_type;
        typedef typename inf2_type::value_type inf2_value_type;
        // e1.d() * e2.v()
        typedef ublas::scalar_multiplies<inf1_value_type, value2_type> functor1_type;
        typedef ublas::vector_binary_scalar2_traits<
            inf1_type, 
            const_value2_type, 
            functor1_type> _Tr1;
        typedef typename _Tr1::expression_type expression1_type;
        // e1.v() * e2.d()
        typedef ublas::scalar_multiplies<value1_type, inf2_value_type> functor2_type;
        typedef ublas::vector_binary_scalar1_traits<
            const_value1_type, 
            inf2_type, 
            functor2_type> _Tr2;
        typedef typename _Tr2::expression_type expression2_type;
        // e1.v() * e2.d() - e1.d() * e2.v()
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
        // e2.v() * e2.v()
        typedef ublas::scalar_binary_functor<value2_type, value2_type> _Tr4;
        typedef typename _Tr4::result_type expression4_type;
        // (e1.v() * e2.d() - e1.d() * e2.v()) / (e2.v() * e2.v())
        typedef typename expression3_type::value_type expression3_value_type;
        typedef expression4_type expression4_value_type;
        typedef ublas::scalar_divides<
            expression3_value_type, 
            expression4_value_type> functor5_type;
        typedef ublas::vector_binary_scalar2_traits<
            expression3_type,
            const expression4_type,
            functor5_type> _Tr5;
    public:
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr5::result_type result_type;
        typedef typename _Tr5::expression_type expression_type;
    public:
        //d1 x d2 -> (d1.d * d2.v - d1.v * d2.d) / d2.v^2
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            // (d1*v2-v1*d2)/(v2*v2) 
            return (e1.d() * e2.v() - e1.v() * e2.d()) / (e2.v() * e2.v());
        }
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_divides_scalar_traits<D1, D2, false> 
    : public dual_inf_vector_divides_vector_traits<D1, D2> {
    };

    template <typename D1, typename D2>
    struct dual_inf_scalar_divides_scalar_traits<D1, D2, true> {
    private:
        //value
        typedef typename D1::value_type value1_type;
        typedef typename D2::value_type value2_type;
        //inf
        typedef typename D1::inf_type inf1_type;
        typedef typename D2::inf_type inf2_type;
        // e1.v() * e2.d()
        typedef ublas::scalar_binary_functor<value1_type, inf2_type> _Tr1;
        // e1.d() * e2.v()
        typedef ublas::scalar_binary_functor<inf1_type, value2_type> _Tr2;
        // e1.v() * e2.d() + e1.d() * e2.v()
        typedef typename _Tr1::result_type expression1_type;
        typedef typename _Tr2::result_type expression2_type;
        typedef ublas::scalar_binary_functor<
            expression1_type, 
            expression2_type> _Tr3;
    public:
        //
        typedef typename D1::const_closure_type argument1_type;
        typedef typename D2::const_closure_type argument2_type;
        typedef typename _Tr3::result_type result_type;
    public:
        //dual x dual -> dual.v * dual.d + dual.d * dual.v
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return e1.v() * e2.d() + e1.d() * e2.v();
        }
    };

    template <typename D1, typename D2>
    struct dual_inf_divides_traits 
    : public dual_inf_scalar_divides_scalar_traits<D1, D2> {
    };

    //dual part
    template <typename D1, typename D2>
    class dual_divides {
    private:
        //value
        typedef dual_value_divides_traits<D1, D2> _VTr;
        //inf
        typedef dual_inf_divides_traits<D1, D2> _ITr;
    public:
        typedef _VTr value_traits;
        typedef _ITr inf_traits;
    };

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_DUAL_FUNCTOR_H_INCLUDED
