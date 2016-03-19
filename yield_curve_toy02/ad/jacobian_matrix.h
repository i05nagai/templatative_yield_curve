#ifndef DDD_AD_JACOBIAN_MATRIX_H_INCLUDED
#define DDD_AD_JACOBIAN_MATRIX_H_INCLUDED

#include "fwd.h"
#include <boost/numeric/ublas/matrix_expression.hpp>

namespace ddd { namespace ad {
    //(a^{1}+b^{1}d, ..., a^{M}+b^{M}d) 
    // or 
    //(a^{1}+b^{1}_{1}d_{1}+...+b^{1}_{N}d_{N}, 
    //..., 
    //a^{M}+b^{M}_{1}d_{1}+...+b^{M}_{N}d_{N}) 
//    template <typename D>
//    struct dual_jacobian_matrix_traits<D, false> {
//    public:
//        typedef typename detail::element_traits<D>::type 
//            value_type;
//        typedef typename value_type::infinitesmal_type 
//            infinitesmal_type;
//        typedef ublas::matrix<value_type> result_type;
//
//    public:
//        //D is vector
//        result_type apply(const D& x)
//        {
//            result_type jac(x.size(), D::size_value);
//
//            for (std::size_t i = 0; i < x.size(); ++i) {
//                for (std::size_t j = 0; j < D::size_value; ++j) {
//                    jac(i, j) = x(i).d()(j);
//                }
//            }
//            return jac;
//        }
//    };
//

    //TODO:
    template <typename D>
    class dual_jacobian_matrix_adapter 
    : ublas::matrix_expression<dual_jacobian_matrix_adapter<D> > {
    private:
        typedef dual_jacobian_matrix_adapter<D> self_type;
        //D::value_type must be dual.
        typedef typename D::inf_type inf_type;//inf_type can be integral.
    public:
        typedef D dual_type;
        typedef typename D::const_closure_type expression_closure_type;
        typedef typename inf_type::value_type value_type; 
        typedef const value_type& const_reference;
        typedef value_type& reference;
        typedef const ublas::matrix_reference<const self_type> 
            const_closure_type;
        typedef ublas::matrix_reference<self_type> closure_type;

        // Construction and destruction
        dual_jacobian_matrix_adapter(const dual_type& e)
        : _size1(e.size()), _size2(e.d().size()), _e(e)
        {
        }

        // Accessors
        size_type size1() const 
        {
            return _size1;
        }

        size_type size2() const 
        {
            return _size2;
        }

    private:
        expression_closure_type _e;
        size_type _size1;
        size_type _size2;
    };



    //a+bd or a+b_{1}d_{1}+...+b_{N}d_{N}
//    template <typename D>
//    struct dual_jacobian_matrix_traits<D, true> {
//    public:
//        typedef typename D::value_type value_type;
//        typedef typename D::infinitesmal_type infinitesmal_type;
//        typedef ublas::vector<value_type> result_type;
//    public:
//        //D is scalar
//        result_type apply(const D& x)
//        {
//            result_type jac(D::size_value);
//
//            for (std::size_t i = 0; i < D::size_value; ++i) {
//                jac(i) = x.d()(i);
//            }
//            
//            return jac;
//        }
//    };


    template <typename D>
    struct jacobian_matrix_traits<D, false>;

    template <typename D>
    struct jacobian_matrix_traits<D, true> 
    : public dual_jacobian_matrix_traits<D> {
    };

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_JACOBIAN_MATRIX_H_INCLUDED

