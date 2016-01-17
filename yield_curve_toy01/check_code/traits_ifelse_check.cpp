#include <iostream>
#include <vector>

template <typename T> 
class dual {
    
};

template <typename T> 
struct is_vector {
    typedef T type;
    static const bool value = false;
};

template <typename T> 
struct is_vector<std::vector<T> > {
    typedef std::vector<T> type;
    static const bool value = true;
};

template <typename T> 
struct is_dual {
    typedef T type;
    static const bool value = false;
};

template <typename T> 
struct is_dual<dual<T> > {
    typedef dual<T> type;
    static const bool value = true;
};

template <typename T, bool Cond = is_vector<T>::value> 
struct vector_condition;

template <typename T> 
struct vector_condition<T, true> {
    static void apply()
    {
        std::cout << "vector" << std::endl;
    }
};

template <typename T> 
struct vector_condition<T, false> {
    static void apply()
    {
        std::cout << "scalar" << std::endl;
    }
};


template <typename T, bool Cond = is_dual<T>::value> 
struct dual_condition;

template <typename T> 
struct dual_condition<T, true> {
    static void apply()
    {
        std::cout << "dual" << std::endl;
    }
};


template <typename T> 
struct dual_condition<T, false> : vector_condition<T> {
    
};


int main(int argc, char const* argv[])
{
    dual_condition<dual<double> >::apply();
    dual_condition<std::vector<double> >::apply();
    dual_condition<std::vector<dual<double> > >::apply();
    dual_condition<double>::apply();
    return 0;
}
