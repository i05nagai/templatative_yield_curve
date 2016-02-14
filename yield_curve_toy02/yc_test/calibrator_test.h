#ifndef DD_YC_TEST_CALIBRATOR_TEST_H_INCLUDED
#define DD_YC_TEST_CALIBRATOR_TEST_H_INCLUDED

#include "ad/dual.h"
#include "yc/calibrator.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace dd { namespace yc_test {
    namespace ublas = boost::numeric::ublas;

    template <typename R>
    class CashFunction {
    public:
        typedef R rate_type;
        typedef rate_type result_type;
    public:
        CashFunction(
            const double startDate, 
            const double endDate, 
            const std::size_t index)
        : _startDate(startDate), _endDate(endDate), _index(index)
        {
        }

        result_type apply(
            const ublas::vector<double>& x,
            const rate_type& rate)
        {
            return (1.0 + (_endDate - _startDate) * rate) * x(_index) 
                - x(_index + 1);
        }
    private:
        double _startDate;
        double _endDate;
        std::size_t _index;
    };

    template <typename R>
    class SwapFunction {
    public:
        typedef R rate_type;
        typedef rate_type result_type;
    public:
        SwapFunction(
            const double startDate, 
            const double endDate, 
            const double frequency, 
            const std::size_t index)
        : _startDate(startDate), _endDate(endDate), _index(index)
        {
        }

        result_type apply(
            const ublas::vector<double>& x,
            const rate_type& rate)
        {
            const double period = (_endDate - _startDate);
            const std::size_t numOfRoll = period / _frequency;

            //fixed-side
            rate_type fixed(0.0);
            for (std::size_t i = 0; i < numOfRoll; ++i) {
                const double dayCountFraction = _frequency;
                fixed = fixed + x(_index + i) * dayCountFraction * rate;
            }

            //floating-side
            rate_type floating(0.0);
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
    };

    bool calibrator_test() {
        typedef ad::dual<double, 2> rate_type;
        typedef rate_type result_type;
        typedef boost::function<
            result_type (const ublas::vector<double>& x)> function_type;

        //cash
        rate_type cashRate(0.0);
        const double startDate1 = 0.0;
        const double endDate1 = 1.0 / 365.0;
        const std::size_t index1 = 0;
        CashFunction<rate_type> cash1(startDate1, endDate1, index1);
        function_type function1 = boost::bind(
            CashFunction<rate_type>::apply, &cash1, _1, cashRate);

        //swap
        rate_type swapRate(0.0);
        const double startDate2 = 0.0 / 365.0;
        const double endDate2 = 1.0;
        const double frequency2 = 0.5;
        const std::size_t index2 = 1;
        SwapFunction<rate_type> swap2(startDate2, endDate2, frequency2, index2);
        function_type function2 = boost::bind(
            SwapFunction<rate_type>::apply, &swap2, _1, swapRate);

        //initial value
        ublas::vector<double> x0(3, 0.5);

        //funciton_type
        ublas::vector<function_type> functions(2);

        typedef yc::NewtonRaphson<function_type> method_type;
        yc::NewtonRaphson<function_type> method(10);
        ublas::vector<double> x 
            = yc::calibrator<function_type, method_type>::apply(functions, method, x0);
    }

} } // namespace dd { namespace yc_test {

#endif // #ifndef DD_YC_TEST_CALIBRATOR_TEST_H_INCLUDED
