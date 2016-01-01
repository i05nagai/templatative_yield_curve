#ifndef AD_VECTOR_EXPRESSION_H_INCLUDED
#define AD_VECTOR_EXPRESSION_H_INCLUDED

namespace ad {
    template <typename E> 
    class vector_expression {
    public:
        typedef E expression_type;

    public:
        const expression_type& operator()() const 
        {
            return static_cast<const expression_type&>(*this);
        }
    };

    template <typename E>
    class vector_reference :
        public vector_expression<vector_reference<E> > {
    private:
        typedef vector_reference self_type;
    public:

    };

    template <typename E, typename Op>
    class vector_unary : 
        public vector_expression<vector_unary<E, Op> > {
    private:
        typedef vector_unary<E, Op> self_type;
    public:
        typedef typename E::size_type size_type;
        typedef typename E::value_type value_type;
        typedef E expression_type;
        typedef typename E::const_closure_type expression_closure_type;
        typedef 
            typename type_traits<typename Op::result_type>::const_reference 
                const_reference;
        typedef const self_type const_closure_type;
    public:
        vector_unary(const expression_type& e)
        : _e(e)
        {
        }

        const_reference operator()(const size_type i) const
        {
            return Op::apply(_e(i));
        }

        size_type size() const
        {
            return _e.size();
        }

    private:
        expression_closure_type _e;
    };

    template <typename E, typename Op>
    struct vector_unary_traits {
        typedef vector_unary<E, Op> expression_type;
        typedef expression_type result_type;
    };

    template <typename E1, typename E2, typename Op>
    class vector_binary : 
        public vector_expression<vector_binary<E1, E2, Op> > {
    private:
        typedef typename E1::size_type size1_type;
        typedef typename E2::size_type size2_type;
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        typedef vector_binary<E1, E2, Op> self_type;
    public:
        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef typename E1::const_closure_type expression1_closure_type;
        typedef typename E2::const_closure_type expression2_closure_type;
        typedef typename 
            promote_traits<size1_type, size2_type>::type size_type;
        typedef typename 
            promote_traits<value1_type, value2_type>::type value_type;
        typedef typename Op::result_type const_reference;
        typedef const self_type const_closure_type;
    public:
        vector_binary(const expression1_type& e1, const expression2_type& e2)
        : _e1(e1), _e2(e2)
        {
        }

        const_reference operator()(const size_type i) const
        {
            return Op::apply(_e1(i), _e2(i));
        }

        size_type size() const
        {
            //TODO:check that e1.size() and e2.size() has same size
            return _e1.size();
        }

    private:
        expression1_closure_type _e1;
        expression2_closure_type _e2;
    };

    template <typename E1, typename E2, typename Op>
    struct vector_binary_traits {
        typedef vector_binary<E1, E2, Op> expression_type;
        typedef expression_type result_type;
    };

} // namespace ad {

#endif // #ifndef AD_VECTOR_EXPRESSION_H_INCLUDED

