#ifndef AD_TYPE_TRAITS_H_INCLUDED
#define AD_TYPE_TRAITS_H_INCLUDED

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

} // namespace ad {

#endif // #ifndef AD_TYPE_TRAITS_H_INCLUDED

