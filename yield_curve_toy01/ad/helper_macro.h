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

#define DISPLAY_DUAL2(x)                                                    \
    std::cout << #x":" << std::endl;                                        \
    std::cout << "  value:" << x.v().v() << std::endl;                      \
    for (std::size_t i = 0; i < x.d().size(); ++i) {                        \
        for (std::size_t j = 0; j < x.d()(i).d().size(); ++j) {             \
            std::cout << "  derivative[" << i << "," << j << "]:"           \
                << x.d()(i).d()(j) << std::endl;                            \
        }                                                                   \
    }

#endif // #ifndef AD_HELPER_MACRO_H_INCLUDED

