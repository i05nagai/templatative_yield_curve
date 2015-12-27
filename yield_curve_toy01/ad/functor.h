#pragma once

namespace ad {
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

    template<typename T1, typename T2>
    struct scalar_mult {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static inline result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            return v1 * v2;
        }
    };

    template<typename T1, typename T2>
    struct scalar_div {
    public:
        typedef typename type_traits<T1>::const_reference argument1_type;
        typedef typename type_traits<T2>::const_reference argument2_type;
        typedef typename promote_traits<T1, T2>::type result_type;
        
        static inline result_type apply(
            argument1_type v1, 
            argument2_type v2)
        {
            //TODO:need to check zero division.
            return v1 / v2;
        }
    };

} // namespace ad {

