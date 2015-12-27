#pragma once

namespace ad {
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

    template <typename E1, typename E2, typename Op>
    struct vector_binary_traits {
        typedef vector_binary<E1, E2, Op> expression_type;
        typedef expression_type result_type;
    };

} // namespace ad {

