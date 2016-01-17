#ifndef AD_TYPE_TRAITS_H_INCLUDED
#define AD_TYPE_TRAITS_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

#include "fwd.h"

namespace ad {
    // default traits
    template <typename T>
    struct type_traits {
    private:
        typedef type_traits<T> self_type;
    public:
        typedef T value_type;
        typedef const T& const_reference;
        typedef T& reference;
    };

    //TODO: need to implement.
    template <typename T1, typename T2>
    struct promote_traits {
        typedef T1 type;
    };

    /*
     * is_dual
     */
    template <typename T, int N = 0> 
    struct is_dual {
        typedef T type;
        static const bool value = false;
    };

    template <typename T, int N> 
    struct is_dual<dual<T, N> > {
        typedef dual<T, N> type;
        static const bool value = true;
    };


    /*
     * is_vector
     */
    template <typename T, bool Cond = boost::is_base_of<
        boost::numeric::ublas::vector_expression<T>, 
        T>::value > 
    struct is_vector;

    template <typename T> 
    struct is_vector<T, false> {
        typedef T type;
        static const bool value = false;
    };

    template <typename T>
    struct is_vector<T, true> {
        typedef T type;
        static const bool value = true;
    };

} // namespace ad {

#endif // #ifndef AD_TYPE_TRAITS_H_INCLUDED

