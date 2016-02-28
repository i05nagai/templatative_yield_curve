#ifndef AD_DUAL_H_INCLUDED
#define AD_DUAL_H_INCLUDED

#include "helper_macro.h"
#include "type_traits.h"
#include "vector_expression.h"
#include "vector.h"

#include <boost/static_assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace ad {
    namespace ublas = boost::numeric::ublas;
    
    template <typename E> 
    class dual_expression {
    public:
        typedef E expression_type;
        typedef typename type_traits<expression_type>::const_reference 
            const_reference;
    public:
        const_reference operator()() const 
        {
            return static_cast<const expression_type&>(*this);
        }
    };

    //scalar dual
    template <typename T, bool Cond = is_dual<T>::value >
    struct scalar_dual_traits;

    //vector<dual>
    template <typename T, bool Cond = boost::mpl::and_<
        is_vector<T>, is_dual<typename T::value_type> >::value>
    struct vector_dual_traits;

    template <typename T>
    struct scalar_dual_traits<T, true> {
    public:
        typedef typename T::infinitesmal_type value_type;
        typedef ublas::vector<value_type> result_type;
    public:
        //d
        static result_type d(const T& d) {
            return d.d();
        }
    };

    template <typename T>
    struct vector_dual_traits<T, false> : scalar_dual_traits<T> {
    };

    template <typename T>
    struct vector_dual_traits<T, true> {
    public:
        typedef typename T::value_type value_type;
        typedef ublas::matrix<value_type> result_type;
    public:
        static result_type apply(const T& d) {
            return d;
        }
    };

    template <typename T, typename I = ublas::vector<T> >
    class dual : public dual_expression<dual<T, I> > {
    private:
        typedef dual<T, I> self_type;
    public:
        typedef T value_type;
        typedef typename type_traits<value_type>::reference reference;
        typedef typename type_traits<value_type>::const_reference
            const_reference;
        typedef I infinitesmal_type;
        typedef typename type_traits<infinitesmal_type>::reference 
            infinitesmal_reference;
        typedef 
            typename type_traits<infinitesmal_type>::const_reference 
                const_infinitesmal_reference;

    public:
        explicit dual() 
        : _value(0), _infinitesmal(0)
        {
        }

        dual(const value_type& value) 
        : _value(value), _infinitesmal(0)
        {
        }

        //TODO:need to check infinitesmal_type is same size.
        dual(
            const value_type& value, 
            const I& infinitesmal) 
        : _value(value), _infinitesmal(infinitesmal)
        {
        }

        reference v() 
        {
            return _value;
        }

        const_reference v() const 
        {
            return _value;
        }

        infinitesmal_reference d()
        {
            return _infinitesmal;
        }

        const_infinitesmal_reference d() const 
        {
            return _infinitesmal;
        }

    private:
        value_type _value;
        infinitesmal_type _infinitesmal;
    };

    namespace detail {
        template <typename T, bool Cond = boost::is_scalar<T>::value>
        struct element_traits;

        //scalar
        template <typename T>
        struct element_traits<T, true> {
        public:
            typedef T type;
        };

        //not scalar
        template <typename T>
        struct element_traits<T, false> {
        public:
            typedef typename T::value_type type;
        };
        
    } // namespace detail

    /*
     * functor traits
     */
    //dual jacobian_matrix: 
    template <typename D, 
        bool Cond = is_scalar_dual<D>::value>
    struct dual_jacobian_matrix_traits;

    //(a^{1}+b^{1}d, ..., a^{M}+b^{M}d) 
    // or 
    //(a^{1}+b^{1}_{1}d_{1}+...+b^{1}_{N}d_{N}, 
    //..., 
    //a^{M}+b^{M}_{1}d_{1}+...+b^{M}_{N}d_{N}) 
    template <typename D>
    struct dual_jacobian_matrix_traits<D, false> {
    public:
        typedef typename detail::element_traits<D>::type 
            value_type;
        typedef typename value_type::infinitesmal_type 
            infinitesmal_type;
        typedef ublas::matrix<value_type> result_type;

    public:
        //D is vector
        result_type apply(const D& x)
        {
            result_type jac(x.size(), D::size_value);

            for (std::size_t i = 0; i < x.size(); ++i) {
                for (std::size_t j = 0; j < D::size_value; ++j) {
                    jac(i, j) = x(i).d()(j);
                }
            }
            return jac;
        }
    };

    //a+bd or a+b_{1}d_{1}+...+b_{N}d_{N}
    template <typename D>
    struct dual_jacobian_matrix_traits<D, true> {
    public:
        typedef typename D::value_type value_type;
        typedef typename D::infinitesmal_type infinitesmal_type;
        typedef ublas::vector<value_type> result_type;
    public:
        //D is scalar
        result_type apply(const D& x)
        {
            result_type jac(D::size_value);

            for (std::size_t i = 0; i < D::size_value; ++i) {
                jac(i) = x.d()(i);
            }
            
            return jac;
        }
    };

    template <typename D, 
         bool Cond = is_dual<D>::value>
    struct jacobian_matrix_traits;

    template <typename D>
    struct jacobian_matrix_traits<D, false>;

    template <typename D>
    struct jacobian_matrix_traits<D, true> 
    : public dual_jacobian_matrix_traits<D> {
    };

    /*
     * dual_operator_traits
     */
    //operator +
    template <typename D1, typename D2, bool Cond = 
        boost::mpl::and_<
            is_vector<typename D1::infinitesmal_type>,
            is_vector<typename D2::infinitesmal_type> >::value>
    struct dual_infinitesmal_vector_plus_vector_traits;

    template <typename D1, typename D2>
    struct dual_infinitesmal_vector_plus_vector_traits<D1, D2, true> {
    public:
        //vector
        typedef typename D1::infinitesmal_type infinitesmal1_type;
        //scalar
        typedef typename D2::infinitesmal_type infinitesmal2_type;
        typedef ublas::scalar_plus<
            typename infinitesmal1_type::value_type, 
            typename infinitesmal2_type::value_type> functor_type;
        typedef ublas::vector_binary_scalar2<
            infinitesmal1_type, 
            infinitesmal2_type, 
            functor_type> result_type;
        typedef typename result_type::expression1_closure_type argument1_type;
        typedef typename result_type::expression2_closure_type argument2_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return result_type(e1.d(), e2.d());
        }
    };

    //scalar + scalar
    template <typename D1, typename D2, bool Cond = 
        boost::mpl::and_<
            boost::is_scalar<typename D1::infinitesmal_type>,
            boost::is_scalar<typename D2::infinitesmal_type> >::value>
    struct dual_infinitesmal_scalar_plus_scalar_traits;

    template <typename D1, typename D2>
    struct dual_infinitesmal_scalar_plus_scalar_traits<D1, D2, false> 
    : public dual_infinitesmal_vector_plus_vector_traits<D1, D2> {
    };

    //D1::I=scalar, D2::I=scalar -> scalar_plus
    template <typename D1, typename D2>
    struct dual_infinitesmal_scalar_plus_scalar_traits<D1, D2, true> {
    public:
        //scalar
        typedef typename D1::infinitesmal_type infinitesmal1_type;
        //scalar
        typedef typename D2::infinitesmal_type infinitesmal2_type;
        typedef ublas::scalar_plus<
            infinitesmal1_type, 
            infinitesmal2_type> functor_type;
        typedef typename functor_type::argument1_type argument1_type;
        typedef typename functor_type::argument2_type argument2_type;
        typedef typename functor_type::reuslt_type result_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return functor_type::apply(e1.d(), e2.d());
        }
    };

    template <typename D1, typename D2>
    struct dual_infinitesmal_plus_traits
    : public dual_infinitesmal_scalar_plus_scalar_traits<D1, D2> {
    };


    /*
    //D1::I=scalar, D2::I=vector -> vector_binary_scalar1
    template <typename D1, typename D2>
    struct dual_infinitesmal_plus_traits {
    public:
        //scalar
        typedef typename D1::infinitesmal_type infinitesmal1_type;
        //vector
        typedef typename D2::infinitesmal_type infinitesmal2_type;
        typedef scalar_plus<
            infinitesmal1_type, 
            typename infinitesmal2_type::value_type> functor_type;
        typedef vector_binary_scalar2<
            infinitesmal1_type, 
            infinitesmal2_type, 
            functor_type> result_type;
        typedef typename result_type::expression1_closure_type argument1_type;
        typedef typename result_type::expression2_closure_type argument2_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return result_type(e1.d(), e2.d());
        }
    };

    //D1::I=vector, D2::I=scalar -> vector_binary_scalar2
    template <typename D1, typename D2>
    struct dual_infinitesmal_plus_traits {
    public:
        //vector
        typedef typename D1::infinitesmal_type infinitesmal1_type;
        //scalar
        typedef typename D2::infinitesmal_type infinitesmal2_type;
        typedef scalar_plus<
            typename infinitesmal1_type::value_type, 
            infinitesmal2_type> functor_type;
        typedef vector_binary_scalar2<
            infinitesmal1_type, 
            infinitesmal2_type, 
            functor_type> result_type;
        typedef typename result_type::expression1_closure_type argument1_type;
        typedef typename result_type::expression2_closure_type argument2_type;
    public:
        static result_type apply(argument1_type e1, argument2_type e2)
        {
            return result_type(e1.d(), e2.d());
        }
    };

    //D1, D2: dual_expression
    template <typename D1, typename D2>
    struct infinitesmal_multiplies {
    public:
        typedef typename ublas::scalar_binary_functor<D1, D2>::argument1_type
            argument1_type;
        typedef typename ublas::scalar_binary_functor<D1, D2>::argument2_type
            argument2_type;
        typedef typename ublas::scalar_binary_functor<D1, D2>::result_type 
            result_type;
    public:
        static result_type apply (argument1_type d1, argument2_type d2) 
        {
            return d1.d() * d2.v() + d1.v() * d2.d();
        }
    };
    */

    template <typename E1, typename E2>
    struct dual_plus {
    public:
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        typedef typename E1::infinitesmal_type infinitesmal1_type;
        typedef typename E2::infinitesmal_type infinitesmal2_type;
        typedef ublas::scalar_plus<value1_type, value2_type> 
            value_functor_type;
        typedef dual_infinitesmal_plus_traits<E1, E2> infinitesmal_functor_type;
    };

    //dual op dual
    //F: dual_functor
    template <typename E1, typename E2, typename F>
    class dual_binary : public dual_expression<dual_binary<E1, E2, F> > {
    private:
        typedef E1 expression1_type;
        typedef E2 expression2_type;
        typedef F functor_type;
        typedef typename functor_type::value_functor_type 
            value_functor_type;
        typedef typename value_functor_type::result_type value_result_type;
        typedef typename functor_type::infinitesmal_functor_type 
            infinitesmal_functor_type;
        typedef typename infinitesmal_functor_type::result_type 
            infinitesmal_result_type;
        typedef typename E1::const_closure_type expression1_closure_type;
        typedef typename E2::const_closure_type expression2_closure_type;
        typedef dual_binary<E1, E2, F> self_type;
    public:
        typedef typename F::result_type value_type;
        typedef value_type const_reference;
        typedef const_reference reference;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;

        // Construction and destruction
        dual_binary(const expression1_type &e1, const expression2_type &e2)
        : _e1(e1), _e2(e2) 
        {
        }
        // Element access
        value_result_type v() const 
        {
            return value_functor_type::apply(_e1, _e2);
        }

        infinitesmal_result_type d() const 
        {
            return infinitesmal_functor_type::apply(_e1, _e2);
        }

    private:
        // Accessors
        const expression1_closure_type& expression1() const 
        {
            return _e1;
        }
        const expression2_closure_type& expression2() const 
        {
            return _e2;
        }

    public:
        // Closure comparison
        bool same_closure(const dual_binary &db) const 
        {
            return (*this).expression1().same_closure(db.expression1()) 
                && (*this).expression2().same_closure(db.expression2());
        }

    private:
        typedef typename E1::const_iterator const_subiterator1_type;
        typedef typename E2::const_iterator const_subiterator2_type;
        typedef const value_type *const_pointer;

    private:
        expression1_closure_type _e1;
        expression2_closure_type _e2;
    };

    //E1: dual_expression<E1>
    //E2: dual_expression<E2>
    //F: dual_binary_functor
    template <typename E1, typename E2, typename F>
    struct dual_binary_traits {
    public:
        typedef typename E1::value_type value1_type;
        typedef typename E2::value_type value2_type;
        typedef typename E1::infinitesmal_type infinitesmal1_type;
        typedef typename E2::infinitesmal_type infinitesmal2_type;
        typedef dual_binary<E1, E2, F> result_type;
        typedef result_type expression_type;
    };

    //dual<V, I> + dual<V, I> -> dual<V+V, I+I>
    template<typename E1, typename E2>
    typename dual_binary_traits<E1, E2, ublas::scalar_plus<E1, E2> >::result_type
    operator +(const dual_expression<E1>& x, const dual_expression<E2>& y)
    {
        typedef dual_binary_traits<E1, E2, dual_plus<E1, E2> > Tr;
        typedef typename Tr::expression_type expression_type;
        return expression_type(x, y);
    }

    /*
    template<typename E1, typename I1, typename E2, typename I2>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator -(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type, N>(x.v() - y.v(), x.d() - y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator *(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        typedef dual<expression_type, N> result_type;
        return result_type(x.v() * y.v(), x.d() * y.v() + x.v() * y.d());
    }

    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator /(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        //TODO: need to check zero division.
        typedef typename promote_traits<E1, E2>::type expression_type;
        typedef dual<expression_type, N> result_type;
        return result_type(x.v() / y.v(), 
            (x.d() * y.v() - x.v() * y.d()) / (y.v() * y.v()));
    }
    */

    /*
    // dual<double> = dual<double> + double
    // T is not dual, not vector, arithmetic.
    template<typename T, typename E, int N>
    dual<E, N> operator +(const dual<E, N>& x, const T& y)
    {
        return x + dual<T, N>(y);
    }
    // dual<double> =  double(constant) + dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator +(const T& x, const dual<E, N>& y)
    {
        return dual<T, N>(x) + y;
    }

    // dual<double> = dual<double> - double(constant)
    template<typename T, typename E, int N>
    dual<E, N> operator -(const dual<E, N>& x, const T& y)
    {
        return x - dual<T, N>(y);
    }
    // dual<double> =  double(constant) - dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator -(const T& x, const dual<E, N>& y)
    {
        return dual<T, N>(x) - y;
    }

    // dual<double> = dual<double> * double(constant)
    template<typename T, typename E, int N>
    dual<E, N> operator *(const dual<E, N>& x, const T& y)
    {
        return x * dual<T, N>(y);
    }
    // dual<double> =  double(constant) * dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator *(const T& x, const dual<E, N>& y)
    {
        return dual<T, N>(x) * y;
    }

    // dual<double> = dual<double> / double(constant)
    template<typename T, typename E, int N>
    dual<E, N> operator /(const dual<E, N>& x, const T& y)
    {
        return x / dual<T, N>(y);
    }
    // dual<double> =  double(constant) / dual<double>
    template<typename T, typename E, int N>
    dual<E, N> operator /(const T& x, const dual<E, N>& y)
    {
        return dual<E, N>(x) / y;
    }
    */

} // namespace ad {


#endif // #ifndef AD_DUAL_H_INCLUDED

