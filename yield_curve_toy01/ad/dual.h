#ifndef AD_DUAL_H_INCLUDED
#define AD_DUAL_H_INCLUDED

#include "helper_macro.h"
#include "type_traits.h"
#include "vector_expression.h"

#include <boost/static_assert.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace ad {
    namespace ublas = boost::numeric::ublas;

    template <typename T>
    class dual_vector : public vector_expression<vector<T> > {
    private:
        typedef dual_vector<T> self_type;
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef std::size_t size_type;
        typedef const self_type& const_closure_type;
        typedef value_type* array_type;

    public:
        explicit dual_vector(const size_type size)
        : _data(new value_type[size]),_size(size)
        {
        }

        explicit dual_vector(const size_type size, const T& value)
        : _data(new value_type[size]),_size(size)
        {
            for (std::size_t i = 0; i < size; ++i) {
                _data[i] = value;
            }
        }

        //copy constructer
        dual_vector(const self_type& other)
        {
            _size = other.size();
            _data = new value_type[_size];
            for (std::size_t i = 0; i < _size; ++i) {
                _data[i] =other._data[i];
            }
        }

        template <typename E>
        dual_vector(const vector_expression<E>& e)
        {
            //TODO:check whether value_type of E is same as the other of vector.
            //TODO:check whether size_type of E is same as the other of vector.
            _size = e().size();
            _data = new value_type[_size];
            for (std::size_t i = 0; i < _size; ++i) {
                _data[i] = e()(i);
            }
        }

        ~dual_vector()
        {
            //TODO: delete_array
            delete[] _data;
        }

        //asign operator
        self_type& operator =(const self_type& other)
        {
            //not self asignment
            if (this != other) {
                self_type v(other);
                swap(v);
            }
            return *this;
        }

        reference operator()(const size_type i)
        {
            return _data[i];
        }

        const_reference operator()(const size_type i) const
        {
            return _data[i];
        }

        size_type size() const
        {
            return _size;
        }

        void swap(self_type& other)
        {
            assert(other.size() == size());
            //T must have a correct asignment operator.
            for (std::size_t i = 0; i < other.size(); ++i) {
                const value_type temp = other._data[i];
                other._data[i] = _data[i];
                _data[i] = temp;
            }
        }

        array_type& data() 
        {
            return _data;
        }

        const array_type& data() const
        {
            return _data;
        }

    private:
       array_type _data;
       size_type _size;
    };


    template <typename T, int N>
    struct derivative_type_traits {
    public:
        typedef dual_vector<T> type;
        typedef typename type_traits<T>::const_reference result_type;
    public:
        static result_type apply(const T& d, const int n) {
            return d;
        }
    };


    template <typename T, int N>
    class dual {
        BOOST_STATIC_ASSERT((N > 0));
    private:
        typedef dual<T, N> self_type;
        typedef dual_vector<T> derivative_type;
    public:
        typedef T value_type;
        typedef typename type_traits<value_type>::reference reference;
        typedef typename type_traits<value_type>::const_reference
            const_reference;
        typedef typename type_traits<derivative_type>::reference 
            derivative_reference;
        typedef 
            typename type_traits<derivative_type>::const_reference 
                const_derivative_reference;

        static const int size_value = N;
        
    public:
        explicit dual() 
        : _value(0), _derivative(N, 0)
        {
        }

        dual(const value_type& value) 
        : _value(value), _derivative(N, 0)
        {
        }

        //TODO:need to check derivative_type is same size.
        template<typename E>
        dual(
            const value_type& value, 
            const vector_expression<E>& derivative) 
        : _value(value), _derivative(derivative)
        {
        }

        reference v() 
        {
            return _value;
        }

        const_reference v() const 
        {
            return _value;
        }

        derivative_reference d()
        {
            return _derivative;
        }

        const_derivative_reference d() const 
        {
            return _derivative;
        }

    private:
        value_type _value;
        derivative_type _derivative;
    };

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator +(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type, N>(x.v() + y.v(), x.d() + y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator -(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type, N>(x.v() - y.v(), x.d() - y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator *(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        typedef dual<expression_type, N> result_type;
        return result_type(x.v() * y.v(), x.d() * y.v() + x.v() * y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator /(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        //TODO: need to check zero division.
        typedef typename promote_traits<E1, E2>::type expression_type;
        typedef dual<expression_type, N> result_type;
        return result_type(x.v() / y.v(), 
            (x.d() * y.v() - x.v() * y.d()) / (y.v() * y.v()));
    }

    // dual<double> = dual<double> + double(constant)
    template<typename E, int N>
    dual<E, N> operator +(const dual<E, N>& x, const E& y)
    {
        return dual<E, N>(x.v() + y, x.d());
    }
    // dual<double> =  double(constant) + dual<double>
    template<typename E, int N>
    dual<E, N> operator +(const E& x, const dual<E, N>& y)
    {
        return dual<E, N>(x + y.v(), y.d());
    }

    // dual<double> = dual<double> - double(constant)
    template<typename E, int N>
    dual<E, N> operator -(const dual<E, N>& x, const E& y)
    {
        return dual<E, N>(x.v() - y, x.d());
    }
    // dual<double> =  double(constant) - dual<double>
    template<typename E, int N>
    dual<E, N> operator -(const E& x, const dual<E, N>& y)
    {
        return dual<E, N>(x - y.v(), y.d());
    }

    // dual<double> = dual<double> * double(constant)
    template<typename E, int N>
    dual<E, N> operator *(const dual<E, N>& x, const E& y)
    {
        return dual<E, N>(x.v() * y, x.d());
    }
    // dual<double> =  double(constant) * dual<double>
    template<typename E, int N>
    dual<E, N> operator *(const E& x, const dual<E, N>& y)
    {
        return dual<E, N>(x * y.v(), y.d());
    }

    // dual<double> = dual<double> / double(constant)
    template<typename E, int N>
    dual<E, N> operator /(const dual<E, N>& x, const E& y)
    {
        return dual<E, N>(x.v() / y, x.d());
    }
    // dual<double> =  double(constant) / dual<double>
    template<typename E, int N>
    dual<E, N> operator /(const E& x, const dual<E, N>& y)
    {
        return dual<E, N>(x / y.v(), y.d());
    }

} // namespace ad {


#endif // #ifndef AD_DUAL_H_INCLUDED

