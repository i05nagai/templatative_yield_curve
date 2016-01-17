#include <cstddef>

#include "../ad/helper_macro.h"

namespace ad {
    template <typename T>
    struct type_traits {
        typedef type_traits<T> self_type;
        typedef T value_type;
        typedef const T& const_reference;
        typedef T& reference;
    };

    //TODO: need to implement.
    template <typename T1, typename T2>
    struct promote_traits {
        typedef T1 type;
    };

    template<typename E> 
    struct vector_expression {
    public:
        typedef E expression_type;

    public:
        inline const expression_type& operator() () const 
        {
            return static_cast<const expression_type&>(*this);
        }
    };

    template<typename E1, typename E2, typename Op>
    struct vector_binary 
        : public vector_expression< vector_binary<E1, E2, Op> > {
    private:
        typedef typename E1::size_type size1_type;
        typedef typename E2::size_type size2_type;
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
    public:
        typedef vector_binary<E1, E2, Op> self_type;
        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef typename 
            promote_traits<size1_type, size2_type>::type size_type;
        typedef typename 
            promote_traits<value1_type, value2_type>::type value_type;
        typedef const self_type const_closure_type;
        typedef typename type_traits<self_type>::const_reference 
            const_reference;

    public:
        inline vector_binary(const expression1_type& e1, const expression2_type& e2)
            : _e1(e1), _e2(e2)
        {
        }

        inline typename Op::result_type operator() (const size_type i) const
        {
            return Op::apply(_e1(i), _e2(i));
        }

        inline size_type size() const
        {
            //TODO:check that e1.size() and e2.size() has same size
            return _e1.size();
        }

    private:
        typename E1::const_closure_type _e1;
        typename E2::const_closure_type _e2;
    };

    template<typename T1, typename T2>
    struct scalar_plus {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static inline result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 + v2;
        }
    };

    template<typename T1, typename T2>
    struct scalar_minus {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        
        static inline result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 - v2;
        }
    };

    template <typename E1, typename E2, typename Op>
    struct vector_binary_traits {
        typedef vector_binary<E1, E2, Op> expression_type;
        typedef expression_type result_type;
    };

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
}

int main(int argc, char const* argv[])
{
    ad::Vector<double> v1(10);
    ad::Vector<double> v2(10);
    ad::Vector<double> v3(10);
    for (std::size_t i = 0; i < v1.size(); ++i) {
        v1(i) = i * 0.1;
        v2(i) = i * 0.2;
        v3(i) = i * 0.3;
    }

    ad::Vector<double> v4 = v1 + v2 - v3;
    DISPLAY_VECTOR_INFOS(v1);
    DISPLAY_VECTOR_INFOS(v2);
    DISPLAY_VECTOR_INFOS(v3);
    DISPLAY_VECTOR_INFOS(v4);
    
    return 0;
}

