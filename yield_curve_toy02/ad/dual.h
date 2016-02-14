#ifndef AD_DUAL_H_INCLUDED
#define AD_DUAL_H_INCLUDED

#include "helper_macro.h"
#include "type_traits.h"
#include "vector_expression.h"
#include "vector.h"

#include <boost/static_assert.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace ad {
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

    template <typename T, int N>
    struct infinitesmal_type_traits {
    public:
        typedef ublas::vector<T> type;
        typedef typename type_traits<T>::const_reference result_type;
    public:
        static result_type apply(const T& d, const int n) {
            return d;
        }
    };


    template <typename T, int N>
    class dual : public dual_expression<dual<T,N> > {
    BOOST_STATIC_ASSERT((N > 0));
    private:
        typedef dual<T, N> self_type;
        typedef ublas::vector<T> infinitesmal_type;
    public:
        typedef T value_type;
        typedef typename type_traits<value_type>::reference reference;
        typedef typename type_traits<value_type>::const_reference
            const_reference;
        typedef typename type_traits<infinitesmal_type>::reference 
            infinitesmal_reference;
        typedef 
            typename type_traits<infinitesmal_type>::const_reference 
                const_infinitesmal_reference;

        static const int size_value = N;
    public:
        explicit dual() 
        : _value(0), _infinitesmal(N, 0)
        {
        }

        dual(const value_type& value) 
        : _value(value), _infinitesmal(N, 0)
        {
        }

        //TODO:need to check infinitesmal_type is same size.
        template<typename E>
        dual(
            const value_type& value, 
            const ublas::vector_expression<E>& infinitesmal) 
        : _value(value), _infinitesmal(infinitesmal)
        {
        }

        reference v() 
        {
            return _value;
        }

        const_reference v() const 
        {
            return _value;
        }

        infinitesmal_reference d()
        {
            return _infinitesmal;
        }

        const_infinitesmal_reference d() const 
        {
            return _infinitesmal;
        }

    private:
        value_type _value;
        infinitesmal_type _infinitesmal;
    };

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator +(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type, N>(x.v() + y.v(), x.d() + y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator -(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type, N>(x.v() - y.v(), x.d() - y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator *(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        typedef dual<expression_type, N> result_type;
        return result_type(x.v() * y.v(), x.d() * y.v() + x.v() * y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator /(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        //TODO: need to check zero division.
        typedef typename promote_traits<E1, E2>::type expression_type;
        typedef dual<expression_type, N> result_type;
        return result_type(x.v() / y.v(), 
            (x.d() * y.v() - x.v() * y.d()) / (y.v() * y.v()));
    }

    // dual<double> = dual<double> + double
    // T is not dual, not vector, arithmetic.
    template<typename T, typename E, int N>
    dual<E, N> operator +(const dual<E, N>& x, const T& y)
    {
        return x + dual<T, N>(y);
    }
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

} // namespace ad {


#endif // #ifndef AD_DUAL_H_INCLUDED
