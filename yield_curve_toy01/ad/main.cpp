#include <cstddef>

#include "helper_macro.h"
#include "vector.h"

int main(int argc, char const* argv[])
{
    ad::Vector<double> v1(10);
    ad::Vector<double> v2(10);
    ad::Vector<double> v3(10);
    for (std::size_t i = 0; i < v1.size(); ++i) {
        v1(i) = i * 0.1;
        v2(i) = i * 0.2;
        v3(i) = i * 0.3;
    }

    ad::Vector<double> v4 = v1 + v2 - v3;
    DISPLAY_VECTOR_INFOS(v1);
    DISPLAY_VECTOR_INFOS(v2);
    DISPLAY_VECTOR_INFOS(v3);
    DISPLAY_VECTOR_INFOS(v4);
    
    return 0;
}

