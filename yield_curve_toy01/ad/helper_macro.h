#pragma once

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
