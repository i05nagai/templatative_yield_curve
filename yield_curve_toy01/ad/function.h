#ifndef AD_FUNCTION_H_INCLUDED
#define AD_FUNCTION_H_INCLUDED

#include "dual.h"
#include "functor.h"
#include "type_traits.h"
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>


namespace ad {
    namespace ublas = boost::numeric::ublas;

    /*
     * exponetial function.
     */
    template <typename E> 
    struct exp_traits {
    private:
        typedef typename promote_traits<E, E>::type value_type;
    public:
        typedef value_type result_type;
        static result_type apply(const E& e)
        {
            return std::exp(e);
        }
    };

    template <typename E>
    typename exp_traits<E>::result_type exp(
        const E& e,
        typename boost::enable_if<boost::is_arithmetic<E> >::type*)
    {
        typedef exp_traits<E> Tr;
        return Tr::apply(e);
    }

    //vector
    template <typename E> 
    struct vector_exp_traits {
    public:
        typedef typename E::value_type value_type;
        typedef scalar_exp<value_type> functor_type;
        typedef typename vector_unary_traits<E, functor_type>::result_type
            result_type;
    public:
        static result_type apply(const vector_expression<E>& e)
        {
            return result_type(e());
        }
    };

    template <typename E>
    typename vector_exp_traits<E>::result_type 
        exp(const vector_expression<E>& e)
    {
        typedef vector_exp_traits<E> Tr;
        return Tr::apply(e());
    }

    //dual
    template <typename E>
    struct dual_exp_traits {
    public:
        typedef typename E::value_type value_type;
        typedef dual<value_type, E::size_value> result_type;
    public:
        static result_type apply(const dual_expression<E>& e)
        {
            return result_type(ad::exp(e().v()), e().d() * ad::exp(e().v()));
        }
    };

    template <typename E>
    typename dual_exp_traits<E>::result_type exp(const dual_expression<E>& e)
    {
        typedef dual_exp_traits<E> Tr;
        return Tr::apply(e());
    }

    /*
     * logarithmic function.
     */
    template <typename E>
    struct log_traits {
    private:
        typedef E value_type;
    public:
        typedef value_type result_type;
        static result_type apply(const E& e)
        {
            return std::log(e);
        }
    };

    template <typename E>
    typename log_traits<E>::result_type log(
        const E& e,
        typename boost::enable_if<boost::is_arithmetic<E> >::type*)
    {
        typedef log_traits<E> Tr;
        return Tr::apply(e);
    }

    //vector
    template <typename E> 
    struct vector_log_traits {
    public:
        typedef typename E::value_type value_type;
        typedef scalar_log<value_type> functor_type;
        typedef typename vector_unary_traits<E, functor_type>::result_type
            result_type;
    public:
        static result_type apply(const vector_expression<E>& e)
        {
            return result_type(e());
        }
    };

    template <typename E>
    typename vector_log_traits<E>::result_type 
        log(const vector_expression<E>& e)
    {
        typedef vector_log_traits<E> Tr;
        return Tr::apply(e());
    }

    //dual
    template <typename E>
    struct dual_log_traits {
    public:
        typedef typename E::value_type value_type;
        typedef dual<value_type, E::size_value> result_type;
    public:
        static result_type apply(const dual_expression<E>& e)
        {
            return result_type(ad::log(e().v()), e().d() * ad::log(e().v()));
        }
    };

    template <typename E>
    typename dual_log_traits<E>::result_type 
        log(const dual_expression<E>& e)
    {
        typedef dual_log_traits<E> Tr;
        return Tr::apply(e());
    }

} // namespace ad {

#endif // #ifndef AD_FUNCTION_H_INCLUDED

