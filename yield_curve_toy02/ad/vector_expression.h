#ifndef AD_VECTOR_EXPRESSION_H_INCLUDED
#define AD_VECTOR_EXPRESSION_H_INCLUDED

#include <boost/numeric/ublas/expression_types.hpp>

namespace ad {
    namespace ublas = boost::numeric::ublas;
    /**
     * vector_functor_traits
     */
    template <typename E, typename Op>
    class vector_functor : 
        public ublas::vector_expression<vector_functor<E, Op> > {
    private:
        typedef vector_functor<E, Op> self_type;
    public:
        typedef typename E::size_type size_type;
        typedef typename E::value_type value_type;
        typedef E expression_type;
        typedef typename E::const_closure_type expression_closure_type;
        typedef value_type const_reference;
        typedef const self_type const_closure_type;
    public:
        vector_functor(const expression_type& e)
        : _e(e)
        {
        }

        const_reference operator()(const size_type i) const
        {
            return Op::apply(_e);
        }

        size_type size() const
        {
            return _e.size();
        }

    private:
        expression_closure_type _e;
    };

} // namespace ad {

#endif // #ifndef AD_VECTOR_EXPRESSION_H_INCLUDED

