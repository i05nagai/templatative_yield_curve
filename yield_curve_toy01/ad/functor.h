#ifndef AD_FUNCTOR_H_INCLUDED
#define AD_FUNCTOR_H_INCLUDED

#include <cmath>

namespace ad {
    /*
     * unary functors
     */
    template <typename T>
    class unary_minus {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(
            argument_type v)
        {
            return -v;
        }
    };

    template <typename T>
    class scalar_exp {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(
            argument_type v)
        {
            return std::exp(v);
        }
    };

    template <typename T>
    class scalar_log {
    public:
        typedef typename type_traits<T>::const_reference argument_type;
        typedef T result_type;

        static result_type apply(
            argument_type v)
        {
            return std::log(v);
        }
    };

    /*
     * binary functors
     */
    template <typename T1, typename T2>
    class scalar_plus {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 + v2;
        }
    };

    template <typename T1, typename T2>
    class scalar_minus {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 - v2;
        }
    };

    template<typename T1, typename T2>
    class scalar_mult {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 * v2;
        }
    };

    template<typename T1, typename T2>
    class scalar_div {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            //TODO:need to check zero division.
            return v1 / v2;
        }
    };

} // namespace ad {

#endif // #ifndef AD_FUNCTOR_H_INCLUDED

