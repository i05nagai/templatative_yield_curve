#ifndef AD_FUNCTION_H_INCLUDED
#define AD_FUNCTION_H_INCLUDED

#include "dual.h"

namespace ad {
    /*
     * exponetial function.
     */
    //E is vector_binary, vector_unary, Vector
    template <typename E>
    struct exp_traits {
    private:
        typedef typename E::value_type value_type;
        typedef scalar_exp<value_type> functor_type;
    public:
        typedef typename vector_unary_traits<E, functor_type>::result_type
            result_type;
        static result_type apply(const vector_expression<E>& e)
        {
            return result_type(e());
        }
    };

    template <typename E>
    typename exp_traits<E>::result_type 
    exp(const vector_expression<E>& e)
    {
        return exp_traits<E>::apply(e);
    }

    template <typename E>
    dual<E> exp(const dual<E>& e)
    {
        return dual<E>(std::exp(e._a), e._b * std::exp(e._a));
    }

    /*
     * logarithmic function.
     */
    //E is vector_unary, vector_binary, double, Vector,
    template <typename E>
    struct log_traits {
    private:
        typedef typename E::value_type value_type;
        typedef scalar_log<value_type> functor_type;
    public:
        typedef typename vector_unary_traits<E, functor_type>::result_type
            result_type;
        static result_type apply(const vector_expression<E>& e)
        {
            return result_type(e());
        }
    };

    template <typename E>
    typename log_traits<E>::result_type log(const vector_expression<E>& e)
    {
        return log_traits<E>::apply(e);
    }

    template <typename E>
    dual<E> log(const dual<E>& e)
    {
        //TODO:need to check value of e._a
        return dual<E>(std::log(e._a), e._b / e._a);
    }
    
} // namespace ad {

#endif // #ifndef AD_FUNCTION_H_INCLUDED

