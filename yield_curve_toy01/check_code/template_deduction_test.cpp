#include <iostream>

template <typename E>
class test {

};

template <typename E>
class base {

};

class derived : public base <derived> {

};

template <typename E>
struct traits {
    static void apply() {
        std::cout << "traits<E>" << std::endl;
    }
};

template <typename E>
struct traits<test<E> > {
    static void apply() {
        std::cout << "traits<test<E> >" << std::endl;
    }
};

template <typename E>
struct traits<base<E> > {
    static void apply() {
        std::cout << "traits<base<E> >" << std::endl;
    }
};

int main(int argc, char const* argv[])
{
    traits<double>::apply();
    traits<test<double> >::apply();
    traits<test<base<test<double> > > >::apply();
    traits<base<derived> >::apply();
    traits<derived>::apply();
    traits<test< base<derived> > >::apply();
    traits<base<test<double> > >::apply();
    return 0;
}

