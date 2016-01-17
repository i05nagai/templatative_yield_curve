#include <iostream>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits.hpp>

template <typename T, int N = 1> 
struct dual {
    typedef T value_type;
    static const int size_value = N;
};

template <typename T, int N = 0> 
struct is_dual {
    typedef T type;
    static const bool value = false;
};

template <typename T, int N> 
struct is_dual<dual<T, N> > {
    typedef dual<T, N> type;
    static const bool value = true;
    static const int n = N;
};


int main(int argc, char const* argv[])
{
    const bool v1 = is_dual<dual<double, 2> >::value;
    const int n1 = is_dual<dual<double, 2> >::n;
    const bool v2 = is_dual<dual<double> >::value;
    const int n2 = is_dual<dual<double> >::n;
    const bool v3 = is_dual<double>::value;
    const bool v4 = is_dual<dual<double, 4> >::value;
    const int n4 = is_dual<dual<double, 4> >::n;
    const bool v5 = is_dual<dual<dual<double>, 4> >::value;
    const int n5 = is_dual<dual<dual<double>, 4> >::n;
    if (v1) std::cout << "v1:" << n1 << std::endl;
    if (v2) std::cout << "v2:" << n2 << std::endl;
    if (v3) std::cout << "v3:" << std::endl;
    if (v4) std::cout << "v4:" << n4 << std::endl;
    if (v5) std::cout << "v5:" << n5 << std::endl;
    return 0;
}

