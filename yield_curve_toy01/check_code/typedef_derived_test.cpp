#include <iostream>

class base {
public:
    typedef int base_type[1];
public:
    base();

    static int apply()
    {
        return sizeof(base_type);
    }
};

class derived : public base {
public:
    typedef int base_type[2];
public:
    derived();

    static int apply()
    {
        return sizeof(base_type);
    }
};

int main(int argc, char const* argv[])
{
    std::cout << base::apply() << std::endl;
    std::cout << derived::apply() << std::endl;
    
    return 0;
}


