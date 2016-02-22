#ifndef DD_YC_TEST_CALIBRATOR_TEST_H_INCLUDED
#define DD_YC_TEST_CALIBRATOR_TEST_H_INCLUDED

#include "ad/function.h"
#include "ad/dual.h"
#include "yc/calibrator.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>


namespace dd { namespace yc_test {
    namespace ublas = boost::numeric::ublas;

    template <typename V, typename R>
    struct CashFunction {
    public:
        typedef R rate_type;
        typedef V value_type;
        typedef typename V::value_type result_type;
    public:
        CashFunction(
            const double startDate, 
            const double endDate, 
            const std::size_t index,
            const rate_type& rate)
        : _startDate(startDate), _endDate(endDate), 
        _index(index), _rate(rate)
        {
        }

        result_type apply(
            const value_type& x)
        {
            return (1.0 + (_endDate - _startDate) * rate) * x(_index) 
                - x(_index + 1);
        }

    private:
        double _startDate;
        double _endDate;
        std::size_t _index;
        rate_type _rate;
    };

    template <typename V, typename R>
    struct SwapFunction {
    public:
        typedef R rate_type;
        typedef V value_type;
        typedef typename V::value_type result_type;
    public:
        SwapFunction(
            const double startDate, 
            const double endDate, 
            const double frequency, 
            const std::size_t index,
            const rate_type& rate)
        : _startDate(startDate), _endDate(endDate), _index(index), _rate(rate)
        {
        }

        //vector_expression?
        result_type operator()(
            const value_type& x)
        {
            const double period = (_endDate - _startDate);
            const std::size_t numOfRoll = period / _frequency;

            //fixed-side
            result_type fixed(0.0);
            for (std::size_t i = 0; i < numOfRoll; ++i) {
                const double dayCountFraction = _frequency;
                fixed = fixed + x(_index + i) * dayCountFraction * rate;
            }

            //floating-side
            result_type floating(0.0);
            for (std::size_t i = 0; i < numOfRoll; ++i) {
                const double dayCountFraction = _frequency;
                floating = floating + x(_index + i) * dayCountFraction 
                    * ((x(_index) / x(_index + 1) - 1.0) / dayCountFraction);
            }

            return fixed - floating;
        }
    private:
        double _startDate;
        double _endDate;
        double _frequency;
        std::size_t _index;
        const rate_type _rate;
    };

    bool calibrator_test() {
        typedef double rate_type;
        typedef ad::dual<double, 3> result_type;
        typedef ublas::vector<result_type> value_type;
        typedef CashFunction<value_type, rate_type> function1_type;
        typedef SwapFunction<value_type, rate_type> function2_type;
        typedef ad::functor2<function1_type, function2_type> 
            function_type; 

        //cash
        const double cashRate = 0.01;
        const double startDate1 = 0.0;
        const double endDate1 = 1.0 / 365.0;
        const std::size_t index1 = 0;
        function1_type cash1(startDate1, endDate1, index1, cashRate);

        //swap
        const double swapRate = 0.04;
        const double startDate2 = 0.0 / 365.0;
        const double endDate2 = 1.0;
        const double frequency2 = 0.5;
        const std::size_t index2 = 1;
        function2_type swap2(startDate2, endDate2, frequency2, index2);

        //initial value
        value_type x0(3);
        x0(0) = 0.5;
        x0(1) = 0.5;
        x0(2) = 0.5;

        //funciton_type
        funciton_type functions(cash1, swap2);

        typedef yc::NewtonRaphson<function_type> method_type;
        yc::NewtonRaphson<function_type> method(10);
        value_type x 
            = yc::calibrator<function_type, method_type>::apply(
                functions, method, x0);
    }

} } // namespace dd { namespace yc_test {

#endif // #ifndef DD_YC_TEST_CALIBRATOR_TEST_H_INCLUDED

