#ifndef AD_FUNCTION_H_INCLUDED
#define AD_FUNCTION_H_INCLUDED

#include "dual.h"
#include "functor.h"
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>

namespace ad {
    namespace ublas = boost::numeric::ublas;

    /*
     * exponetial function.
     */
    template <typename E, bool Cond = is_vector<E>::value>
    struct vector_exp_traits;

    template <typename E> 
    struct vector_exp_traits<E, true> {
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
    struct vector_exp_traits<E, false> {
    private:
        typedef E value_type;
    public:
        typedef value_type result_type;
        static result_type apply(const E& e)
        {
            return std::exp(e);
        }
    };

    template <typename E, bool Cond = is_dual<E>::value>
    struct dual_exp_traits;
    
    //dual
    template <typename E>
    struct dual_exp_traits<E, true> {
    public:
        typedef typename E::value_type value_type;
        typedef dual<value_type, E::size_value> result_type;
    public:
        static result_type apply(const E& e)
        {
            return result_type(ad::exp(e.v()), e.d() * ad::exp(e.v()));
        }
    };

    template <typename E>
    struct dual_exp_traits<E, false> : public vector_exp_traits<E> {
    };

    template <typename E> 
    struct exp_traits : public dual_exp_traits<E> {
    };


    /*
    template <typename E, typename T>
    struct exp_traits {
    private:
        typedef E value_type;
    public:
        typedef value_type result_type;
        static result_type apply(const E& e)
        {
            return std::exp(e);
        }
    };

    
    template <typename E>
    struct exp_traits<dual<E> > {
    private:
    public:
        typedef E value_type;
        typedef dual<E> result_type;
    public:
        static result_type apply(const dual<E>& e)
        {
            return result_type(std::exp(e.v()), e.d() * std::exp(e.v()));
        }
    };

    template <typename E>
    struct exp_traits<E,
        typename boost::enable_if< 
            boost::is_base_of<vector_expression<E>, E> >::type> {
    private:
        
        typedef scalar_exp<value_type> functor_type;
    public:
        typedef typename vector_unary_traits<E, functor_type>::result_type
            result_type;
        static result_type apply(const vector_expression<E>& e)
        {
            return result_type(e());
        }
    };
    */

    template <typename E>
    typename exp_traits<E>::result_type exp(const E& e)
    {
        typedef exp_traits<E> Tr;
        return Tr::apply(e);
    }

    /*
     * logarithmic function.
     */
    template <typename E, typename T>
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
    struct log_traits<dual<E> > {
    private:
    public:
        typedef E value_type;
        typedef dual<E> result_type;
        static result_type apply(const dual<E>& e)
        {
            return result_type(std::log(e.v()), e.d() / e.v());
        }
    };

    template <typename E>
    struct log_traits<E,
        typename boost::enable_if< 
            boost::is_base_of<vector_expression<E>, E> >::type> {
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
    typename log_traits<E>::result_type log(const E& e)
    {
        typedef log_traits<E> Tr;
        return Tr::apply(e);
    }

} // namespace ad {

#endif // #ifndef AD_FUNCTION_H_INCLUDED

