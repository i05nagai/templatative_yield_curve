#ifndef DD_DETAIL_NUMBERGENERATOR_H_INCLUDED
#define DD_DETAIL_NUMBERGENERATOR_H_INCLUDED

#include <boost/random.hpp>

namespace ddd { namespace detail {
    class NumberGenerator {
    public:
        NumberGenerator(
            const double min = 0.0, const double max = 1.0)
        : _rng(), _dist(min, max),_generator(_rng, _dist)
        {
        }

        double operator()()
        {
            return _generator();
        }
    private:
        boost::mt19937 _rng;
        boost::uniform_real<> _dist;
        boost::variate_generator<
            boost::mt19937&, boost::uniform_real<> > _generator;
    };
} } // namespace ddd { namespace detail {

#endif // #ifndef DD_DETAIL_NUMBERGENERATOR_H_INCLUDED
