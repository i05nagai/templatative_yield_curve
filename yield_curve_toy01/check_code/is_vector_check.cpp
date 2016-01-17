#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

template <typename T, bool Cond = boost::is_base_of<
    boost::numeric::ublas::vector_expression<T>, 
    T>::value > 
struct is_vector;

template <typename T> 
struct is_vector<T, false> {
    typedef T type;
    static const bool value = false;
};

template <typename T>
struct is_vector<T, true> {
    typedef T type;
    static const bool value = true;
};


int main(int argc, char const* argv[])
{
    namespace ublas = boost::numeric::ublas;
    const bool v1 = is_vector<ublas::vector<double> >::value;
    const bool v2 = is_vector<ublas::vector<ublas::vector<double> > >::value;
    const bool v3 = is_vector<double>::value;
    const bool v4 = is_vector<ublas::vector_expression<double> >::value;
    const bool v5 = is_vector<ublas::vector<ublas::vector_expression<double> > >::value;
    if (v1) std::cout << "v1:" << std::endl;
    if (v2) std::cout << "v2:" << std::endl;
    if (v3) std::cout << "v3:" << std::endl;
    if (v4) std::cout << "v4:" << std::endl;
    if (v5) std::cout << "v5:" << std::endl;
    return 0;
}

