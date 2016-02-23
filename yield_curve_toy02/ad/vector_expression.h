#ifndef AD_VECTOR_EXPRESSION_H_INCLUDED
#define AD_VECTOR_EXPRESSION_H_INCLUDED

#include <boost/numeric/ublas/expression_types.hpp>

namespace ad {
    namespace ublas = boost::numeric::ublas;
    /**
     * vector_functor_traits
     */
    template <typename E, typename F>
    class vector_functor : 
        public ublas::vector_expression<vector_functor<E, F> > {
    private:
        typedef vector_functor<E, F> self_type;
    public:
        typedef typename E::size_type size_type;
        typedef typename E::value_type value_type;
        typedef E expression_type;
        typedef typename E::const_closure_type expression_closure_type;
        typedef value_type const_reference;
        typedef const self_type const_closure_type;
        typedef F function_type;
    public:
        vector_functor(
            const expression_type& e,
            const function_type& f)
        : _e(e), _f(f)
        {
        }

        const_reference operator()(const size_type i) const
        {
            return _f(i)(_e);
        }

        size_type size() const
        {
            return _e.size();
        }

    private:
        expression_closure_type _e;
        function_type _f;
    };

} // namespace ad {

#endif // #ifndef AD_VECTOR_EXPRESSION_H_INCLUDED

