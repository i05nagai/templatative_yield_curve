#ifndef DDD_AD_FUNCTION_H_INCLUDED
#define DDD_AD_FUNCTION_H_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "ad/dual.h"
#include "ad/functor.h"
#include "ad/type_traits.h"

namespace ddd { namespace ad {
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
        typedef typename ublas::vector_unary_traits<
            E, functor_type>::result_type result_type;
    public:
        static result_type apply(const ublas::vector_expression<E>& e)
        {
            return result_type(e());
        }
    };

    template <typename E>
    typename vector_exp_traits<E>::result_type 
    exp(const ublas::vector_expression<E>& e)
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
        typedef typename ublas::vector_unary_traits<
            E, functor_type>::result_type result_type;
    public:
        static result_type apply(const ublas::vector_expression<E>& e)
        {
            return result_type(e());
        }
    };

    template <typename E>
    typename vector_log_traits<E>::result_type log(
        const ublas::vector_expression<E>& e)
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
            return result_type(
                ad::log(e().v()), e().d() * ad::log(e().v()));
        }
    };

    template <typename E>
    typename dual_log_traits<E>::result_type 
        log(const dual_expression<E>& e)
    {
        typedef dual_log_traits<E> Tr;
        return Tr::apply(e());
    }

    /*
     * matrix inverse
     */ 
    template <typename E>
    struct invert_traits {
    private:
        typedef invert_traits<E> this_type;
    public:
        typedef typename E::value_type value_type;
        typedef E result_type;
    public:
        static result_type apply()
        {
        }
    };

    //TODO:check whether satisfies following specifications.
    //T is matrix -> inverse matrix
    //T is vector -> inverse matrix which interprets vector as matrix
    //T is scalar -> inverse matrix which interprets scalar as matrix
    template <typename E>
    typename invert_traits<E>::result_type invert(const E& e)
    {
        typedef typename E::value_type value_type;
        typedef ublas::matrix<value_type> matrix_type;

        BOOST_UBLAS_CHECK(
            e.size1() == e.size2(), ublas::external_logic());

        matrix_type lhs(e);
        matrix_type rhs(ublas::identity_matrix<value_type>(e.size1()));
        ublas::permutation_matrix<> pm(e.size1());

        ublas::lu_factorize(lhs, pm);
        ublas::lu_substitute(lhs, pm, rhs);

        BOOST_UBLAS_CHECK(
            rhs.size1() == e.size1(), ublas::internal_logic());
        BOOST_UBLAS_CHECK(
            rhs.size2() == e.size2(), ublas::internal_logic());

        return rhs;
    }

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_FUNCTION_H_INCLUDED

