#ifndef AD_FUNCTION_H_INCLUDED
#define AD_FUNCTION_H_INCLUDED

#include "dual.h"
#include "functor.h"

namespace ad {
    /*
     * exponetial function.
     */

    template <typename E>
    struct exp_traits<vector_expression<E> > {
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

    double exp(const double e)
    {
        return std::exp(e);
    }

    template <typename E> dual<E> exp(const dual<E>& e)
    {
        return dual<E>(std::exp(e.v()), e.d() * std::exp(e.v()));
    }

    template <typename E>
    typename exp_traits<vector_expression<E> >::result_type 
    exp(const vector_expression<E>& e)
    {
        typedef exp_traits<vector_expression<E> > Tr;
        return Tr::apply(e);
    }

    /*
     * logarithmic function.
     */
    //E is vector_expression
    template <typename E>
    struct log_traits<vector_expression<E> > {
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

    double log(const double e)
    {
        return std::log(e);
    }

    template <typename E> dual<E> log(const dual<E>& e)
    {
        return dual<E>(std::log(e.v()), e.d() / e.v());
    }

    template <typename E>
    typename log_traits<vector_expression<E> >::result_type 
        log(const vector_expression<E>& e)
    {
        typedef log_traits<vector_expression<E> > Tr;
        return Tr::apply(e);
    }

} // namespace ad {

#endif // #ifndef AD_FUNCTION_H_INCLUDED

