#include <iostream>


template <typename T, int N = 1> class dual;

template <typename T, int N> 
class dual {
    
};

template <typename T, int N = 0> 
struct arity_traits_impl;

template <typename T, int N> 
struct arity_traits_impl<dual<T>, N> {
    static void apply()
    {
        std::cout << "impl:" << N << std::endl;
    }
};

template <typename T> 
struct arity_traits {
    static void apply()
    {
        arity_traits_impl<T>::apply();
    }
};


int main(int argc, char const* argv[])
{
    arity_traits<dual<void, 2> >::apply();
    return 0;
}

