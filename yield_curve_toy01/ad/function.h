#ifndef AD_FUNCTION_H_INCLUDED
#define AD_FUNCTION_H_INCLUDED

namespace ad {
    template <typename E>
    struct exp_traits {
    private:
        typedef typename E::value_type value_type;
        typedef unary_exp<value_type> functor_type;
    public:
        typedef typename vector_unary_traits<E, functor_type>::result_type
            result_type;
        static result_type apply(const E& e)
        {
            return result_type(e);
        }
    };

    template <typename E>
    typename exp_traits<E>::result_type exp(const vector_expression<E>& e)
    {
        return exp_traits<E>::apply(e);
    }

    template <typename E>
    struct log_traits {
    private:
        typedef typename E::value_type value_type;
        typedef unary_log<value_type> functor_type;
    public:
        typedef typename vector_unary_traits<E, functor_type>::result_type
            result_type;
        static result_type apply(const E& e)
        {
            return result_type(e);
        }
    };

    template <typename E>
    typename log_traits<E>::result_type log(const vector_expression<E>& e)
    {
        return log_traits<E>::apply(e);
    }
    
} // namespace ad {

#endif // #ifndef AD_FUNCTION_H_INCLUDED

