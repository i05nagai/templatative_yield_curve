#ifndef DDD_AD_HELPER_FUNCTION_H_INCLUDED
#define DDD_AD_HELPER_FUNCTION_H_INCLUDED

namespace ddd { namespace ad {
    namespace ublas = boost::numeric::ublas;
    template <typename V>
    dual<V> make_constant(const V& v, const std::size_t size = 0)
    {
        return dual<V>(v, ublas::vector<V>(size));
    }

    template <typename V>
    dual<V> make_variable(
        const V& v, 
        const std::size_t size, 
        const std::size_t position)
    {
        assert(position < size);
        ublas::vector<V> d(size, 0);
        d(position) = 1;
        return dual<V>(v, d);
    }

    
} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_HELPER_FUNCTION_H_INCLUDED
