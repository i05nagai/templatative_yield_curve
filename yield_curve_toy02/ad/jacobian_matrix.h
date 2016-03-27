/**
 * @file jacobian_matrix.h
 * @brief 
 * @author i05nagai
 * @version 0.0.1
 * @date 2016-03-27
 */

#ifndef DDD_AD_JACOBIAN_MATRIX_H_INCLUDED
#define DDD_AD_JACOBIAN_MATRIX_H_INCLUDED

#include <boost/numeric/ublas/matrix_expression.hpp>
#include "fwd.h"

namespace ddd { namespace ad {

    namespace detail {

        /**
         * @brief
         * D is vector<dual<V, I> >.
         * V is scalar.
         * I is vector.
         */
        template <typename D>
        class jacobian_matrix_adapter_vector_dual<D, true> {
        private:
            //self_type
            typedef jacobian_matrix_adapter_vector_dual<D, true> self_type;
            //dual_type
            typedef D dual_type;
            typedef typename D::value_type element_type;
            typedef typename element_type::infinitesimal_type 
                infinitesimal_type;
            typedef typename infinitesimal_type::value_type 
                infinitesimal_value_type;
        public:
            //expression_type
            typedef typename D::const_closure_type expression_closure_type;
            //size_type
            typedef std::size_t size_type;
            //difference
            typedef std::ptrdiff_t difference_type;
            //reference
            typedef infinitesimal_value_type const_reference;
            typedef const_reference reference;
            //closure
            typedef const self_type const_closure_type;
            typedef self_type closure_type;
        public:
            jacobian_matrix_adapter_vector_dual(const dual_type& e)
            : _e(e), _size1(_e.size()), _size2(_e(0).d().size())
            {
            }

            //TODO:need copy constructor?

            const_reference operator()(
                size_type i, 
                size_type j) const
            {
                assert(i >= 0);
                assert(_size1 >= i);
                assert(j >= 0);
                assert(_size2 >= j);
                return _e(i).d()(j);
            }

            reference operator()(
                size_type i, 
                size_type j)
            {
                return _e(i).d()(j);
            }

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

        /**
         * @brief
         * D is vector<dual<V, I> >.
         * V is scalar.
         * I is scalar.
         */
        template <typename D>
        class jacobian_matrix_adapter_vector_dual<D, false> {
        private:
            //self_type
            typedef jacobian_matrix_adapter_vector_dual<D, false> self_type;
            typedef D dual_type;
            typedef typename D::value_type element_type;
            typedef typename element_type::infinitesimal_type 
                infinitesimal_type;
        public:
            //expression_type
            typedef typename D::const_closure_type expression_closure_type;
            //size
            typedef std::size_t size_type;
            //difference
            typedef std::ptrdiff_t difference_type;
            //reference
            typedef infinitesimal_type const_reference;
            typedef const_reference reference;
            //closure
            typedef const self_type const_closure_type;
            typedef self_type closure_type;
        public:
            jacobian_matrix_adapter_vector_dual(const dual_type& e)
            : _e(e), _size1(_e.size()), _size2(1)
            {
            }
            
            //TODO:need copy constructor?

            const_reference operator()(
                size_type i, 
                size_type j) const
            {
                assert(i >= 0);
                assert(_size1 > i);
                assert(j == 0);
                return _e(i).d();
            }

            reference operator()(
                size_type i, 
                size_type j)
            {
                assert(i >= 0);
                assert(_size1 > i);
                assert(j == 0);
                return _e(i).d();
            }

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

        /**
         * @brief
         * D is dual<V, I>.
         * V is scalar.
         * I is vector.
         */
        template <typename D>
        class jacobian_matrix_adapter_scalar_dual<D, true> {
        private:
            //self_type
            typedef jacobian_matrix_adapter_scalar_dual<D, true> self_type;
            //dual_type
            typedef D dual_type;
            //infinitesimal_type
            typedef typename D::infinitesimal_type 
                infinitesimal_type;
            typedef typename infinitesimal_type::value_type 
                infinitesimal_value_type;
        public:
            //expression_type
            typedef typename D::const_closure_type expression_closure_type;
            //size_type
            typedef std::size_t size_type;
            //difference
            typedef std::ptrdiff_t difference_type;
            //reference
            typedef infinitesimal_value_type const_reference;
            typedef const_reference reference;
            //closure
            typedef const self_type const_closure_type;
            typedef self_type closure_type;
        public:
            jacobian_matrix_adapter_scalar_dual(const dual_type& e)
            : _e(e), _size1(1), _size2(_e.d().size())
            {
            }

            //TODO:need copy constructor?

            const_reference operator()(
                size_type i, 
                size_type j) const
            {
                assert(i == 0);
                assert(j >= 0);
                assert(j < _size2);
                return _e.d()(j);
            }

            reference operator()(
                size_type i, 
                size_type j)
            {
                assert(i == 0);
                assert(j >= 0);
                assert(j < _size2);
                return _e.d()(j);
            }

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

        /**
         * @brief
         * D is dual<V, I>.
         * V is scalar.
         * I is scalar.
         */
        template <typename D>
        class jacobian_matrix_adapter_scalar_dual<D, false> {
        private:
            //self_type
            typedef jacobian_matrix_adapter_scalar_dual<D, false> self_type;
            //dual_type
            typedef D dual_type;
            //infinitesimal_type
            typedef typename D::infinitesimal_type infinitesimal_type;
        public:
            //expression_type
            typedef typename D::const_closure_type expression_closure_type;
            //size_type
            typedef std::size_t size_type;
            //difference
            typedef std::ptrdiff_t difference_type;
            //reference
            typedef infinitesimal_type const_reference;
            typedef const_reference reference;
            //closure
            typedef const self_type const_closure_type;
            typedef self_type closure_type;
        public:
            jacobian_matrix_adapter_scalar_dual(const dual_type& e)
            : _e(e)
            {
            }

            //TODO:need copy constructor?

            const_reference operator()(
                size_type i, 
                size_type j) const
            {
                assert(i == 0);
                assert(j == 0);
                return _e.d();
            }

            reference operator()(
                size_type i, 
                size_type j)
            {
                assert(i == 0);
                assert(j == 0);
                return _e.d();
            }

            size_type size1() const 
            {
                return 1;
            }

            size_type size2() const 
            {
                return 1;
            }

        private:
            expression_closure_type _e;
        };

        template <typename D>
        class jacobian_matrix_adapter_impl<D, true>
        : public jacobian_matrix_adapter_vector_dual<D> {
        private:
            typedef D dual_type;
        public:
            jacobian_matrix_adapter_impl(const dual_type& e)
            : jacobian_matrix_adapter_vector_dual<D>(e)
            {
            }
        };

        template <typename D>
        class jacobian_matrix_adapter_impl<D, false>
        : public jacobian_matrix_adapter_scalar_dual<D> {
        private:
            typedef D dual_type;
        public:
            jacobian_matrix_adapter_impl(const dual_type& e)
            : jacobian_matrix_adapter_scalar_dual<D>(e)
            {
            }
        };

    } // namespace detail

    /*--------------------------------------------------------------------------
     * dual_jacobian_matrix_adapter
     *------------------------------------------------------------------------*/
    template <typename D>
    class dual_jacobian_matrix_adapter 
    : ublas::matrix_expression<dual_jacobian_matrix_adapter<D> > {
    private:
        typedef D dual_type;
        //self_type
        typedef dual_jacobian_matrix_adapter<D> self_type;
        //impl
        typedef typename detail::jacobian_matrix_adapter_impl<D> _Impl;
    public:
        //size_type
        typedef typename _Impl::size_type size_type;
        //reference
        typedef typename _Impl::const_reference const_reference;
        typedef typename _Impl::reference reference;
        //closure
        typedef const ublas::matrix_reference<const self_type> 
            const_closure_type;
        typedef ublas::matrix_reference<self_type> closure_type;

        // Construction and destruction
        dual_jacobian_matrix_adapter(const dual_type& e)
        : _impl(e)
        {
        }

        const_reference operator()(size_type i, size_type j) const 
        {
            return _impl(i, j);
        }

        reference operator()(size_type i, size_type j) 
        {
            return _impl(i, j);
        }

        // Accessors
        size_type size1() const 
        {
            return _impl.size1();
        }

        size_type size2() const 
        {
            return _impl.size2();
        }

        //TODO:define interator

    private:
        _Impl _impl;
    };

} } // namespace ddd { namespace ad {

#endif // #ifndef DDD_AD_JACOBIAN_MATRIX_H_INCLUDED

