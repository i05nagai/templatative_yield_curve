#pragma once

#include <cstddef>

#include "type_traits.h"
#include "functor.h"
#include "vector_expression.h"

namespace ad {
    template <typename E1, typename E2> 
    typename vector_binary_traits<E1, E2, scalar_plus<typename E1::value_type, typename E2::value_type> >::result_type
        operator + (
            const vector_expression<E1>& e1, 
            const vector_expression<E2>& e2)
    {
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        typedef 
            typename vector_binary_traits<E1, E2, scalar_plus<value1_type, value2_type> >
                ::expression_type expression_type;
        return expression_type(e1(), e2());
    }

    template <typename E1, typename E2> 
    typename vector_binary_traits<E1, E2, scalar_minus<typename E1::value_type, typename E2::value_type> >::result_type
        operator - (
            const vector_expression<E1>& e1, 
            const vector_expression<E2>& e2)
    {
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        typedef 
            typename vector_binary_traits<E1, E2, scalar_minus<value1_type, value2_type> >
                ::expression_type expression_type;
        return expression_type(e1(), e2());
    }

    template <typename E1, typename E2> 
    typename vector_binary_traits<E1, E2, scalar_mult<typename E1::value_type, typename E2::value_type> >::result_type
        operator * (
            const vector_expression<E1>& e1, 
            const vector_expression<E2>& e2)
    {
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        typedef 
            typename vector_binary_traits<E1, E2, scalar_mult<value1_type, value2_type> >
                ::expression_type expression_type;
        return expression_type(e1(), e2());
    }

    template <typename T>
    class Vector : public vector_expression< Vector<T> > {
    public:
        typedef Vector<T> self_type;
        typedef T value_type;
        typedef std::size_t size_type;
        typedef const self_type& const_closure_type;
    private:

    public:
        explicit Vector(const size_type size)
            : _data(new value_type[size]),_size(size)
        {
        }

        //copy constructer
        Vector(const self_type& other)
        {
            _size = other.size();
            _data = new value_type[_size];
            for (std::size_t i = 0; i < _size; ++i) {
                _data[i] =other._data[i];
            }
        }

        template <typename E>
        Vector(const vector_expression<E>& e)
        {
            //TODO:check whether value_type of E is same as one of Vector.
            //TODO:check whether size_type of E is same as one of Vector.
            _size = e().size();
            _data = new value_type[_size];
            for (std::size_t i = 0; i < _size; ++i) {
                _data[i] = e()(i);
            }
        }

        ~Vector()
        {
            delete[] _data;
        }

        //asign operator
        self_type& operator = (const self_type& other)
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

        value_type& operator () (const size_type i)
        {
            return _data[i];
        }

        const value_type& operator () (const size_type i) const
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
} // namespace ad {

