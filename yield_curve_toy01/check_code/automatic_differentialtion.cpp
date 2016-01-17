#include <iostream>
#include "../ad/helper_macro.h"

namespace ad {
    //TODO: need to implement.
    template <typename T1, typename T2>
    struct promote_traits {
        typedef T1 type;
    };
        
    template <typename T>
    struct Dual {
        typedef Dual<T> self_type;
        typedef T value_type;

        explicit Dual() 
            : _a(0.0), _b(1.0)
        {
        }

        Dual(T a, T b = 0.0) 
            : _a(a), _b(b)
        {
        }
        static Dual<T> d()
        {
            return Dual<T>(T(0.0), T(1.0));
        }

        T _a;
        T _b;
    };

    template<typename E1, typename E2>
    Dual<typename promote_traits<E1, E2>::type> 
        operator + (const Dual<E1>& x, const Dual<E2>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return Dual<expression_type>(x._a + y._a, x._b + y._b);
    }

    template<typename E1, typename E2>
    Dual<typename promote_traits<E1, E2>::type> 
        operator * (const Dual<E1>& x, const Dual<E2>& y)
    {
        return Dual<E1>(x._a * y._a, x._b * y._a + x._a * y._b);
    }
    
    template <typename T>
    inline T func(T x)
    {
        typedef typename T::value_type value_type;
        return (x + Dual<value_type>(2.0)) * (x + Dual<value_type>(1.0));
    }

} // namespace ad


int main(int argc, char const* argv[])
{
    using ad::Dual;
    Dual<double> d(3.0, 1.0);
    const Dual<double>& result = ad::func(d);
    std::cout << result._a << std::endl;
    std::cout << result._b << std::endl;

    //what i want to do
    //ad::Vector< ad::Dual<double> > x(2);
    //x(0) = 2.0;
    //x(1) = 3.0;
    //const ad::Vector<ad::Dual<double> >& result = func(x);

    return 0;
}

