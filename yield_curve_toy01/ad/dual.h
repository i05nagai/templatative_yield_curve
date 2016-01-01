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

        explicit dual() 
            : _a(0.0), _b(0.0)
        {
        }

        dual(T a, T b = 0.0) 
            : _a(a), _b(b)
        {
        }

        T _a;
        T _b;
    };

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator +(const dual<E1>& x, const dual<E2>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x._a + y._a, x._b + y._b);
    }

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator -(const dual<E1>& x, const dual<E2>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x._a - y._a, x._b - y._b);
    }

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator *(const dual<E1>& x, const dual<E2>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x._a * y._a, x._b * y._a + x._a * y._b);
    }

    template<typename E1, typename E2>
    dual<typename promote_traits<E1, E2>::type> 
        operator /(const dual<E1>& x, const dual<E2>& y)
    {
        //TODO: need to check zero division.
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type>(x._a / y._a, (x._b * y._a - x._a * y._b) / (y._a * y._a));
    }

    // dual<double> = dual<double> + double(constant)
    template<typename E>
    dual<E> operator +(const dual<E>& x, const E& y)
    {
        return dual<E>(x._a + y, x._b);
    }

    // dual<double> =  double(constant) + dual<double>
    template<typename E>
    dual<E> operator +(const E& x, const dual<E>& y)
    {
        return dual<E>(x + y._a, y._b);
    }

} // namespace ad {


#endif // #ifndef AD_DUAL_H_INCLUDED

