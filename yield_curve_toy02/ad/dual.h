#ifndef DDD_AD_DUAL_H_INCLUDED
#define DDD_AD_DUAL_H_INCLUDED

#include "dual_functor.h"
#include "helper_macro.h"
#include "type_traits.h"
#include "vector_expression.h"
#include "vector.h"
#include "ad/dual_expression.h"
#include "ad/dual_expression.h"

#include <boost/static_assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/utility/enable_if.hpp>

namespace ddd { namespace ad {
    namespace ublas = boost::numeric::ublas;

    template <typename V, typename I = ublas::vector<V> >
    class dual : public dual_expression<dual<V, I> > {
    private:
        typedef dual<V, I> self_type;
    public:
        typedef V value_type;
        typedef V& value_reference;
        typedef const V& const_value_reference;
        //inf
        typedef I infinitesimal_type;
        typedef I& infinitesimal_reference;
        typedef const I& const_infinitesimal_reference;
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
        : _v(ae().v()), _d()
        {

        }

        dual(const value_type& value) 
        : _v(value), _d(0)
        {
        }

        //TODO:need to check inf_type is same size.
        dual(
            const value_type& value, 
            const infinitesimal_type& d) 
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

        infinitesimal_reference d()
        {
            return _d;
        }

        const_infinitesimal_reference d() const
        {
            return _d;
        }

    private:
        value_type _v;
        infinitesimal_type _d;
    };

//    //E1 is not dual
//    template<typename E1, typename E2, typename VF, typename IF>
//    class dual_binary_scalar1 
//    : public dual_expression<dual_binary_scalar1<E1, E2, VF, IF> > {
//        typedef E1 expression1_type;
//        typedef E2 expression2_type;
//        typedef VF value_functor_type;
//        typedef IF infinitesimal_functor_type;
//        typedef const E1& expression1_closure_type;
//        typedef typename E2::const_closure_type expression2_closure_type;
//        typedef dual_binary<E1, E2, VF, IF> self_type;
//
//    public:
//        //value
//        typedef typename value_functor_type::result_type 
//            value_type;
//        typedef value_type const_value_reference;
//        typedef const_value_reference value_reference;
//        //infinitesimal
//        typedef typename infinitesimal_functor_type::result_type 
//            infinitesimal_type;
//        typedef infinitesimal_type const_infinitesimal_reference;
//        typedef const_infinitesimal_reference infinitesimal_reference;
//        //closure
//        typedef const self_type const_closure_type;
//        typedef const_closure_type closure_type;
//
//        // Construction and destruction
//        dual_binary_scalar1(const expression1_type& e1, const expression2_type& e2)
//        : _e1(e1), _e2(e2)
//        {
//        }
//
//    public:
//        // Element access
//        const_value_reference v() const 
//        {
//            return value_functor_type::apply(_e1, _e2);
//        }
//
//        const_infinitesimal_reference d() const 
//        {
//            return infinitesimal_functor_type::apply(_e1, _e2);
//        }
//
//    private:
//        expression1_closure_type _e1;
//        expression2_closure_type _e2;
//    };
//
//
//    template<typename E1, typename E2, typename VF, typename IF>
//    struct dual_binary_scalar1_traits {
//        typedef dual_binary_scalar1<E1, E2, VF, IF> expression_type;
//        typedef expression_type result_type; 
//        typedef result_type type;
//    };

    // dual<double> =  double(constant) + dual<double>
//    template<typename T, typename E>
//    typename boost::lazy_enable_if<
//        boost::mpl::not_<is_dual<T> >,
//        dual_binary_scalar1_traits<
//            T, 
//            E, 
//            value_plus<T, E>,
//            infinitesimal_plus<T, E> 
//        >
//    >::type
//    operator +(const T& x, const dual_expression<E>& y)
//    {
//        typedef dual_binary_scalar1_traits<
//            T, 
//            E, 
//            value_plus<T, E>,
//            infinitesimal_plus<T, E> 
//        > _Tr;
//        typedef typename _Tr::expression_type expression_type;
//        return expression_type(x, y);
//    }

    /*
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

