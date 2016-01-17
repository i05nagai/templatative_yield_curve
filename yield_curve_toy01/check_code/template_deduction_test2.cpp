#include <iostream>

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
struct traits<base<E> > {
    static void apply() {
        std::cout << "traits<base<E> >" << std::endl;
    }
};

int main(int argc, char const* argv[])
{
    traits<derived>::apply();
    return 0;
}
