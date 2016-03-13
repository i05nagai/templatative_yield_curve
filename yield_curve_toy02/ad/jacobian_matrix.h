#ifndef DDD_AD_JACOBIAN_MATRIX_H_INCLUDED
#define DDD_AD_JACOBIAN_MATRIX_H_INCLUDED

#include "fwd.h"

namespace ddd { namespace ad {
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


    template <typename D>
    struct jacobian_matrix_traits<D, false>;

    template <typename D>
    struct jacobian_matrix_traits<D, true> 
    : public dual_jacobian_matrix_traits<D> {
    };

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_JACOBIAN_MATRIX_H_INCLUDED

