#ifndef AD_DUAL_H_INCLUDED
#define AD_DUAL_H_INCLUDED

#include "helper_macro.h"
#include "type_traits.h"

namespace ad {
    template <typename T>
    class dual {
    private:
        typedef dual<T> self_type;
    public:
        typedef T value_type;
        typedef typename type_traits<value_type>::reference reference;
        typedef typename type_traits<value_type>::const_reference 
            const_reference;

    public:
        explicit dual() 
            : _value(0.0), _derivative(0.0)
        {
        }

        dual(const value_type& value, const value_type& derivative = 0.0) 
            : _value(value), _derivative(derivative)
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

        reference d()
        {
            return _derivative;
        }
        const_reference d() const 
        {
            return _derivative;
        }

    private:
        value_type _value;
        value_type _derivative;
    };

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator +(const dual<E1>& x, const dual<E2>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x.v() + y.v(), x.d() + y.d());
    }

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator -(const dual<E1>& x, const dual<E2>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x.v() - y.v(), x.d() - y.d());
    }

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator *(const dual<E1>& x, const dual<E2>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x.v() * y.v(), x.d() * y.v() + x.v() * y.d());
    }

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator /(const dual<E1>& x, const dual<E2>& y)
    {
        //TODO: need to check zero division.
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x.v() / y.v(), (x.d() * y.v() - x.v() * y.d()) / (y.v() * y.v()));
    }

    // dual<double> = dual<double> + double(constant)
    template<typename E>
    dual<E> operator +(const dual<E>& x, const E& y)
    {
        return dual<E>(x.v() + y, x.d());
    }

    // dual<double> =  double(constant) + dual<double>
    template<typename E>
    dual<E> operator +(const E& x, const dual<E>& y)
    {
        return dual<E>(x + y.v(), y.d());
    }

} // namespace ad {


#endif // #ifndef AD_DUAL_H_INCLUDED

