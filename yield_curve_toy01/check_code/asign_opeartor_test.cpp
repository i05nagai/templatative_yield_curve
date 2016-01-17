

struct Base {
    
};

struct Derived : public Base {
    
};

struct Vector : public Base {
    Vector(const Base& b)
    {
    }
};

int main(int argc, char const* argv[])
{
    Derived hoge;
    Vector v = hoge;
    return 0;
}
