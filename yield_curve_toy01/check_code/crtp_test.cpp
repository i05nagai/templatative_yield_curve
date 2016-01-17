
#include <iostream>
#include <typeinfo.h>

template <typename T>
struct Base {
    const T& operator() () const
    {
        return static_cast<const T&>(*this);
    }
};

struct Derived : public Base<Derived> {

};

struct Vector : public Base<Vector> {
    typedef Vector self_type;
    typedef Base<self_type> base_type;

    Vector()
    {
    }

    Vector(const base_type& b)
    {
    }
};

#define TYPE_CHECK_MACRO(a, type_name) \
    if (typeid((a)) == typeid(type_name)) { \
        std::cout << #a "is " #type_name  << std::endl; \
    } 

int main(int argc, char const* argv[])
{
    Derived d1;
    Vector v1;
    const Base<Derived>& b1 = d1;
    const Base<Vector>& b2 = v1;
    TYPE_CHECK_MACRO(b1(), Derived);
    TYPE_CHECK_MACRO(b1(), Vector);
    TYPE_CHECK_MACRO(b2(), Derived);
    TYPE_CHECK_MACRO(b2(), Vector);
    return 0;
}
