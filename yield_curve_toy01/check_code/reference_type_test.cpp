
template <typename T>
void f0(T& param) 
{
}

template <typename T>
void f1(const T& param) 
{
}

template <typename T>
void f2(T* param) 
{
}

template <typename T>
void f3(T&& param) 
{
}

template <typename T>
void f4(T param) 
{
}

template <typename T>
void f5(T param) 
{
}

void g(int);

template <typename T>
struct type_traits {
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
};

class test {
public:
    test() {}
    test(int i) {}
};

int main(int argc, char const* argv[])
{
    {
        int x = 0;
        const int cx = 0;
        const int& cxr = cs;
        f0(x);      //T=int,        param=int&
        f0(cx);     //T=const int,  param=const int&
        f0(cxr);    //T=const int,  param=const int&
        f0(g);      //T=void (&)(int);
    }
    {
        int x = 0;
        const int cx = 0;
        const int& cxr = cs;
        f1(x);      //T=int,  param=const int&
        f1(cx);     //T=int,  param=const int&
        f1(cxr);    //T=int,  param=const int&
    }
    {
        int x = 0;
        int* px = &x;
        f2(x);      //T=int,        param=int*
        f2(px);     //T=const int,  param=const int*
    }
    {
        int x = 0;
        const int cx = 0;
        const int& cxr = x;
        f3(27);       //rvalue, T=int,        param=int&&
        f3(x);        //lvalue, T=int&,       param=int&
        f3(cx);       //lvalue, T=const int&, param=const int&
        f3(cxr);      //lvalue, T=const int&, param=const int&
    }
    {
        int x = 0;
        const int cx = 0;
        const int& cxr = x;
        const char* p = "abc";
        f4(27);       //rvalue, T=param=int
        f4(x);        //lvalue, T=param=int
        f4(cx);       //lvalue, T=param=int
        f4(cxr);      //lvalue, T=param=int
        f4(p);        //lvalue, T=param=const char*
        f4(g);        //T=void (*)(int);
    }
    {
        int hoge1 = 10;
        int hoge2 = 20;
        int hoge3 = 30;
        typedef const int& type_type;
        typedef const type_type& type;
        typedef typename type_traits<type>::value_type value_type;
        typedef typename type_traits<type>::const_reference const_reference;
        typedef typename type_traits<type>::reference reference;
        reference hogeR1 = hoge1;
        const_reference hogeR2 = hoge2;
        const_reference hogeR3 = hoge3;
        hogeR1 = 1;
        hogeR2 = 1;
        hogeR3 = 1;
    }

    return 0;
}

