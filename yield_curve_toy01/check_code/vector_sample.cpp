#include <cstddef>

template <typename T>
class Vector {
public:
    typedef T value_type;
    typedef std::size_t size_type;
private:

public:
    explicit Vector(const std::size_t size)
        : _data(new value_type[size]),_size(size)
    {
    }

    //copy constructer
    Vector(const Vector<value_type>& other)
    {
        _size = other.size();
        _data = new value_type[_size];
        for (std::size_t i = 0; i < _size; ++i) {
            _data[i] =other._data[i];
        }
    }

    ~Vector()
    {
        delete[] _data;
    }

    //asign operator
    Vector<value_type>& operator = (const Vector<value_type>& other)
    {
        //not self asignment
        if (this != other) {
            //T must have a correct asignment operator.
            _data = new value_type[other.size()];
            for (std::size_t i = 0; i < other.size(); ++i) {
                _data[i] = other._data[i];
            }
        }
        return *this;
    }

    const value_type& operator () (std::size_t i) const
    {
        return _data[i];
    }

    size_type size() const
    {
        return _size;
    }

private:
   value_type* _data;
   size_type _size;
};

int main(int argc, char const* argv[])
{
    Vector<double> v(10);
    for (std::size_t i = 0; i < v.size(); ++i) {
        v[i] = i * 0.1;
    }
    Vector<double> v1(10);
    Vector<double> v2 = v;
    for (std::size_t i = 0; i < v.size(); ++i) {
        v1[i] = i * 0.2;
    }

    Vector<double> v3 = v1 + v2;

    return 0;
}

