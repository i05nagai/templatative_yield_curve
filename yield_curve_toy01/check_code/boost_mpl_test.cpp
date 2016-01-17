#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <iostream>


template <typename E>
class vector_expression {
    
    public:
        vector_expression(){}
};

template <typename E>
class vector : public vector_expression<vector<E> >{
    
    public:
        vector(){}
};

template <typename E>
class sample {
    public:
        sample() {}
};

template <typename E, typename T = void> struct traits;
template <typename E> typename traits<E>::type hoge(const E& e);

template <typename E, typename T>
struct traits {
    typedef E type;
    static void apply()
    {
        std::cout << "default" << std::endl;
    }
};

template <typename E>
struct traits<sample<E> > {
    typedef E type;
    static void apply()
    {
        std::cout << "specialization for sample<E>" << std::endl;
    }
};

template <typename E>
struct traits<E, typename boost::enable_if<
    boost::is_base_of<vector_expression<E>, E> >::type> {
    typedef E type;
    static void apply()
    {
        std::cout << "is_base_of vector_expression<E>" << std::endl;
    }
};


int main(int argc, char const* argv[])
{
    vector<double> a;

    traits<double>::apply();
    traits<sample<double> >::apply();
    traits<vector<double> >::apply();
    return 0;
}
