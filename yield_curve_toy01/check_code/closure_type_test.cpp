
struct Base {
    
};

struct Derived : public Base {
    
};

struct binary {
    double apply(double& a1, double& a2) const
    {
        return a1 + a2;
    }
}

struct Vector : public Base {
    Vector(const Base& b)
    {
    }

    double& operator() (const std::size_t i)
    {
        return _a;
    }

private:
    double _a;
};

int main(int argc, char const* argv[])
{
    Derived hoge;
    Vector v = hoge;
    
    return 0;
}
