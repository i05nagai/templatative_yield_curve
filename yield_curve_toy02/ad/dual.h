#ifndef DDD_AD_DUAL_H_INCLUDED
#define DDD_AD_DUAL_H_INCLUDED

#include "dual_functor.h"
#include "helper_macro.h"
#include "type_traits.h"
#include "vector_expression.h"
#include "vector.h"

#include <boost/static_assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/utility/enable_if.hpp>

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

    template <typename V, typename I = ublas::vector<V> >
    class dual : public dual_expression<dual<V, I> > {
    private:
        typedef dual<V, I> self_type;
    public:
        typedef V value_type;
        typedef V& value_reference;
        typedef const V& const_value_reference;
        //inf
        typedef I inf_type;
        typedef I& inf_reference;
        typedef const I& const_inf_reference;
        //
        typedef const self_type& const_reference;
        typedef self_type& reference;
        typedef const self_type& const_closure_type;

    public:
        explicit dual() 
        : _v(0), _d(0)
        {
        }

        template <typename AE>
        dual(const dual_expression<AE>& ae) 
        : _v(ae().v()), _d(ae().d())
        {
        }

        dual(const value_type& value) 
        : _v(value), _d(0)
        {
        }

        //TODO:need to check inf_type is same size.
        dual(
            const value_type& value, 
            const inf_type& d) 
        : _v(value), _d(d)
        {
        }

        value_reference v()
        {
            return _v;
        }

        const_value_reference v() const
        {
            return _v;
        }

        inf_reference d()
        {
            return _d;
        }

        const_inf_reference d() const
        {
            return _d;
        }

    private:
        value_type _v;
        inf_type _d;
    };

    /*
     * dual_operator_traits
     */
    template <typename D1, typename D2, typename F>
    struct dual_binary_traits {
    private:
        typedef F functor_type;
    public:
        //value
        typedef typename F::value_traits value_traits;
        typedef typename value_traits::result_type value_result_type;
        //inf
        typedef typename F::inf_traits inf_traits;
        typedef typename inf_traits::result_type inf_result_type;
        //
        typedef dual<value_result_type, inf_result_type> result_type;
        typedef result_type expression_type;
    };

    //dual<V, I> + dual<V, I> -> dual<V+V, I+I>
    template <typename E1, typename E2>
    typename dual_binary_traits<E1, E2, dual_plus<E1, E2> >::result_type
    operator +(const dual_expression<E1>& e1, const dual_expression<E2>& e2)
    {
        typedef dual_binary_traits<E1, E2, dual_plus<E1, E2> > Tr;
        //value
        typedef typename Tr::value_traits value_traits;
        typedef typename Tr::value_result_type value_result_type;
        //inf
        typedef typename Tr::inf_traits inf_traits;
        typedef typename Tr::inf_result_type inf_result_type;
        //expression
        typedef typename Tr::expression_type expression_type;

        return expression_type(
            value_traits::apply(e1(), e2()), 
            inf_traits::apply(e1(), e2()));
    }

    //dual<V, I> - dual<V, I> -> dual<V-V, I-I>
    template <typename E1, typename E2>
    typename dual_binary_traits<E1, E2, dual_minus<E1, E2> >::result_type
    operator -(const dual_expression<E1>& e1, const dual_expression<E2>& e2)
    {
        typedef dual_binary_traits<E1, E2, dual_minus<E1, E2> > Tr;
        //value
        typedef typename Tr::value_traits value_traits;
        typedef typename Tr::value_result_type value_result_type;
        //inf
        typedef typename Tr::inf_traits inf_traits;
        typedef typename Tr::inf_result_type inf_result_type;
        //expression
        typedef typename Tr::expression_type expression_type;

        return expression_type(
            value_traits::apply(e1(), e2()), 
            inf_traits::apply(e1(), e2()));
    }

    //dual<V1, I1> * dual<V2, I2> -> dual<V1*V2, V1*I2+I1*V2>
    template <typename E1, typename E2>
    typename dual_binary_traits<E1, E2, dual_multiplies<E1, E2> >::result_type
    operator *(const dual_expression<E1>& e1, const dual_expression<E2>& e2)
    {
        typedef dual_binary_traits<E1, E2, dual_multiplies<E1, E2> > Tr;
        //value
        typedef typename Tr::value_traits value_traits;
        //inf
        typedef typename Tr::inf_traits inf_traits;
        //expression
        typedef typename Tr::expression_type expression_type;

        return expression_type(
            value_traits::apply(e1(), e2()), 
            inf_traits::apply(e1(), e2()));
    }

    //dual<V1, I1> / dual<V2, I2> -> dual<V1/V2, (I1*V2-V1*I2)/(V2*V2)>
    template <typename E1, typename E2>
    typename dual_binary_traits<E1, E2, dual_divides<E1, E2> >::result_type
    operator /(const dual_expression<E1>& e1, const dual_expression<E2>& e2)
    {
        typedef dual_binary_traits<E1, E2, dual_divides<E1, E2> > Tr;
        //value
        typedef typename Tr::value_traits value_traits;
        //inf
        typedef typename Tr::inf_traits inf_traits;
        //expression
        typedef typename Tr::expression_type expression_type;

        return expression_type(
            value_traits::apply(e1(), e2()), 
            inf_traits::apply(e1(), e2()));
    }

    namespace detail {
        template <typename V1, typename I1, typename T>
        struct dual_plus_not_dual_traits {
        public:
            typedef typename dual_binary_traits<
                dual<V1, I1>, 
                dual<T, I1>,
                dual_plus<dual<V1, I1>, dual<T, I1> > >::result_type type;
        };
    } // namespace detail

    // dual<double> = dual<double> + double
    // T is not dual, not vector, arithmetic.
    // TODO:need to modify dual binary operators to make these kind of operations available.
//    template<typename V1, typename I1, typename T>
//    typename boost::lazy_enable_if<
//        boost::mpl::not_<is_dual<T> >, 
//        detail::dual_plus_not_dual_traits<V1, I1, T> >::type
//    operator +(const dual<V1, I1>& x, const T& y)
//    {
//        static dual<T, I1> d(1.0, I1(0));
//        d.v() = y;
//        d.d().resize(x.d().size());
//        return x + dual<double>(2.0, I1(2));
//    }

    /*
    // dual<double> =  double(constant) + dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator +(const T& x, const dual<E, N>& y)
    {
        return dual<T, N>(x) + y;
    }

    // dual<double> = dual<double> - double(constant)
    template<typename T, typename E, int N>
    dual<E, N> operator -(const dual<E, N>& x, const T& y)
    {
        return x - dual<T, N>(y);
    }
    // dual<double> =  double(constant) - dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator -(const T& x, const dual<E, N>& y)
    {
        return dual<T, N>(x) - y;
    }

    // dual<double> = dual<double> * double(constant)
    template<typename T, typename E, int N>
    dual<E, N> operator *(const dual<E, N>& x, const T& y)
    {
        return x * dual<T, N>(y);
    }
    // dual<double> =  double(constant) * dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator *(const T& x, const dual<E, N>& y)
    {
        return dual<T, N>(x) * y;
    }

    // dual<double> = dual<double> / double(constant)
    template<typename T, typename E, int N>
    dual<E, N> operator /(const dual<E, N>& x, const T& y)
    {
        return x / dual<T, N>(y);
    }
    // dual<double> =  double(constant) / dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator /(const T& x, const dual<E, N>& y)
    {
        return dual<E, N>(x) / y;
    }
    */

} } // namespace ddd { namespace ad {


#endif // #ifndef DDD_AD_DUAL_H_INCLUDED

