#ifndef AD_HELPER_MACRO_H_INCLUDED
#define AD_HELPER_MACRO_H_INCLUDED


#include <iostream>

#define DISPLAY_VECTOR_ELEMENTS(v)                      \
    for (std::size_t i = 0; i < v.size(); ++i) {        \
       std::cout << v(i) << ", ";                       \
    }                                                   \
    std::cout << std::endl;

#define DISPLAY_VECTOR_INFOS(v)                         \
    std::cout << "var_name:" << #v << std::endl;        \
    std::cout << "size:" << v.size() << std::endl;      \
    for (std::size_t i = 0; i < v.size(); ++i) {        \
       std::cout << i << ":" << v(i) << std::endl;      \
    }                                                   

#define DISPLAY_VAR(v)                                  \
    std::cout << #v ":" << v << std::endl;

#define DISPLAY_DUAL(x)                                                     \
    std::cout << #x":" << std::endl;                                        \
    std::cout << "  value:" << x.v() << std::endl;                          \
    for (std::size_t i = 0; i < x.d().size(); ++i) {                        \
        std::cout << "  derivative" << i << ":" << x.d()(i) << std::endl;   \
    }

#define AD_DEFINE_SCALAR_VECTOR_OPERATOR(op, OP)                            \
    template <typename T1, typename E2>                                     \
    typename vector_binary_scalar1_traits<                                  \
        T1,                                                                 \
        E2,                                                                 \
        OP <                                                                \
            T1,                                                             \
            typename E2::value_type> >::result_type                         \
        operator op (                                                       \
            const T1& e1,                                                   \
            const vector_expression<E2>& e2)                                \
    {                                                                       \
        typedef T1 value1_type;                                             \
        typedef typename E2::value_type value2_type;                        \
        typedef typename vector_binary_scalar1_traits<T1, E2, OP <          \
            value1_type,                                                    \
            value2_type> >::expression_type expression_type;                \
        return expression_type(e1, e2());                                   \
    }

#define AD_DEFINE_VECTOR_SCALAR_OPERATOR(op, OP)                            \
    template <typename T1, typename E2>                                     \
    template <typename E1, typename T2>                                     \
    typename vector_binary_scalar2_traits<                                  \
        E1,                                                                 \
        T2,                                                                 \
        OP <                                                                \
            typename E1::value_type,                                        \
            T2> >::result_type                                              \
         operator op (                                                      \
            const vector_expression<E1>& e1,                                \
            const T2& e2)                                                   \
    {                                                                       \
        typedef typename E1::value_type value1_type;                        \
        typedef T2 value2_type;                                             \
        typedef typename vector_binary_scalar2_traits<E1, T2, OP <          \
            value1_type,                                                    \
            value2_type> >::expression_type expression_type;                \
        return expression_type(e1(), e2);                                   \
    }

#endif // #ifndef AD_HELPER_MACRO_H_INCLUDED

