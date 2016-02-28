#ifndef DDD_YC_CALIBRATOR_H_INCLUDED
#define DDD_YC_CALIBRATOR_H_INCLUDED

#include "ad/type_traits.h"
#include <boost/type_traits/remove_reference.hpp>

namespace ddd { namespace yc {

    template <typename F>
    struct functor_traits;

    template <typename F>
    class NewtonRaphson {
    private:
        typedef NewtonRaphson<F> this_type;
        typedef functor_traits<F> _Tr;
    public:
        typedef typename _Tr::function_type function_type;
        typedef typename _Tr::result_type function_result_type;
        typedef typename _Tr::arg1_type argument_type;
        typedef typename boost::remove_reference<argument_type>::type 
            argument_closure_type;
        typedef const argument_closure_type argument_const_closure_type;
        typedef argument_type result_type;

    public:
        NewtonRaphson(const std::size_t numberOfTrial)
        : _numberOfTrial(numberOfTrial)
        {
        }

        result_type optimize(
            const function_type& f, 
            const argument_type& x0) const
        {
            argument_closure_type x1 = x0;
            argument_closure_type x2;
            function_result_type y = f(x1);
            std::size_t count = 1;

            while(this->isConverged(x1, x2, count))
            {
                x1 = x2;
                const function_result_type& r = f(x1);
                x2 = x1 - ad::invert(r.d()) * y;
                y = r.v();
                ++count;
            }
        }

    private:
        bool isConverged(
            argument_const_closure_type x1,
            argument_const_closure_type x2,
            std::size_t& count) const
        {
            return norm(x1, x2) < std::numeric_limits<argument_closure_type>::epsilon()
                || count > _numberOfTrial;
        }
        
        std::size_t _numberOfTrial;
    };

    template <typename F, typename M, bool Cond = ad::is_vector<F>::value>
    struct calibrator_traits;

    template <typename F, typename M>
    struct calibrator_traits<F, M, false> {
    private:
        typedef calibrator_traits<F, M, false> this_type;
    public:
        typedef F function_type;
        typedef typename F::arg1_type argument_type;
        typedef M method_type;
        typedef typename M::result_type result_type;
    public:
    private:
    };

    template <typename F, typename M>
    struct calibrator_traits<F, M, true> {
    private:
        typedef calibrator_traits<F, M, true> this_type;
    public:
        typedef typename F::value_type function_type;
        typedef typename function_type::arg1_type argument_type;
        typedef M method_type;
        typedef typename M::result_type result_type;
    public:
    private:
    };

    template <typename F, typename M>
    struct calibrator {
    private:
        typedef calibrator<F, M> this_type;
        typedef calibrator_traits<F, M> _Tr;
    public:
        typedef typename _Tr::function_type function_type;
        typedef typename _Tr::argument_type argument_type;
        typedef typename _Tr::method_type method_type;
        typedef typename _Tr::result_type result_type;
    public:
        static result_type apply(
            const function_type& f,
            const method_type& m,
            const argument_type& x0)
        {
            return m.optimize(x0);
        }

    private:

    };

    
} } // namespace ddd { namespace yc {

#endif // #ifndef DDD_YC_CALIBRATOR_H_INCLUDED

