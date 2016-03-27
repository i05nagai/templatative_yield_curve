/**
 * @file helper_function.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-03-27
 */

#ifndef DDD_AD_HELPER_FUNCTION_H_INCLUDED
#define DDD_AD_HELPER_FUNCTION_H_INCLUDED

namespace ddd { namespace ad {
    namespace ublas = boost::numeric::ublas;

    /**
     * @brief Making constant dual object.
     *
     * @tparam V type of constant value.
     * @param v constant value.
     * @param size the number of variables.
     *
     * @return constant dual object.
     */
    template <typename V>
    dual<V> 
    make_constant(const V& v, const std::size_t size = 0)
    {
        return dual<V>(v, ublas::vector<V>(size));
    }

    /**
     * @brief Making unit dual object.
     *
     * @tparam V type of constant value.
     * @param v constant value.
     * @param size the number of variables.
     * @param position 
     *
     * @return 
     */
    template <typename V>
    dual<V> 
    make_variable(
        const V& v, 
        const std::size_t size, 
        const std::size_t position)
    {
        assert(position < size);
        ublas::vector<V> d(size, 0);
        d(position) = 1;
        return dual<V>(v, d);
    }

    /**
     * @brief 
     *
     * @tparam V
     * @param v
     * @param size
     *
     * @return 
     */
    template <typename V>
    ublas::vector<dual<V> > 
    make_unit_vector_dual(
        const V& v,
        const std::size_t size)
    {
        typedef ublas::vector<V> infinitesimal_type;
        typedef dual<V, infinitesimal_type> dual_type;
        typedef ublas::vector<dual_type> result_type;

        result_type unitVectorDual(size);

        for (std::size_t i = 0; i < size; ++i) {
            unitVectorDual(i) = make_variable(v, size, i);
        }

        return unitVectorDual;
    }
    
} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_HELPER_FUNCTION_H_INCLUDED

