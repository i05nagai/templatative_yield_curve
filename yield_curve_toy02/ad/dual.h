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

    template <typename T, int N>
    class dual : public dual_expression<dual<T,N> > {
    BOOST_STATIC_ASSERT((N > 0));
    private:
        typedef dual<T, N> self_type;
    public:
        typedef T value_type;
        typedef typename type_traits<value_type>::reference reference;
        typedef typename type_traits<value_type>::const_reference
            const_reference;
        typedef ublas::vector<T> infinitesmal_type;
        typedef typename type_traits<infinitesmal_type>::reference 
            infinitesmal_reference;
        typedef 
            typename type_traits<infinitesmal_type>::const_reference 
                const_infinitesmal_reference;

        static const int size_value = N;
    public:
        explicit dual() 
        : _value(0), _infinitesmal(N, 0)
        {
        }

        dual(const value_type& value) 
        : _value(value), _infinitesmal(N, 0)
        {
        }

        //TODO:need to check infinitesmal_type is same size.
        template<typename E>
        dual(
            const value_type& value, 
            const ublas::vector_expression<E>& infinitesmal) 
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
    //dual jacobian: 
    template <typename D, 
        bool Cond = is_scalar_dual<D>::value>
    struct dual_jacobian_traits;

    //(a^{1}+b^{1}d, ..., a^{M}+b^{M}d) 
    // or 
    //(a^{1}+b^{1}_{1}d_{1}+...+b^{1}_{N}d_{N}, 
    //..., 
    //a^{M}+b^{M}_{1}d_{1}+...+b^{M}_{N}d_{N}) 
    template <typename D>
    struct dual_jacobian_traits<D, false> {
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
    struct dual_jacobian_traits<D, true> {
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
    struct jacobian_traits;

    template <typename D>
    struct jacobian_traits<D, false>;

    template <typename D>
    struct jacobian_traits<D, true> : dual_jacobian_traits<D> {
    };

    /*
     * dual operators
     */
    template<typename E1, typename E2, int N>
    dual<typename promote_traits<E1, E2>::type, N> 
        operator +(const dual<E1, N>& x, const dual<E2, N>& y)
    {
        typedef typename promote_traits<E1, E2>::type expression_type;
        return dual<expression_type, N>(x.v() + y.v(), x.d() + y.d());
    }

    template<typename E1, typename E2, int N>
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

} // namespace ad {


#endif // #ifndef AD_DUAL_H_INCLUDED

