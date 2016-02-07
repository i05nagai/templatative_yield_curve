#ifndef YC_CURVE_CURVE_H_INCLUDED
#define YC_CURVE_CURVE_H_INCLUDED

#include "yc/curve/interpolator.h"

namespace yc { namespace curve {
    // point <= first -> first
    // ith < point <= jth-> jth
    // end <= point -> end(c)
    template <typename G, typename V> 
    std::size_t find_first(const G& g, const V& v)
    {
        for (std::size_t i = 0; i < g.size(); ++i) {
            if (v < g[i]) {
                return i;
            }
        }
        return g.size();
    }
} } // namespace yc { namespace curve {

namespace yc { namespace curve {
    template <typename G, typename V, typename I> 
    class curve {
    private: 
        typedef curve<G, V, I> this_type;
    public:
        typedef I interporation_type;
        typedef G grid_type;
        typedef typename G::value_type grid_value_type;
        typedef V data_type;
        typedef typename V::value_type data_value_type;

    public:
        curve(const grid_type& grid, const data_type& data)
        : _grid(grid), _data(data)
        {
        }

        data_value_type operator()(const grid_value_type& point)
        {
            return interpolator<I>::apply(_grid, _data, point);
        }
    private:
        grid_type _grid;
        data_type _data;
    };
} } // namespace yc { namespace curve {

#endif // #ifndef YC_CURVE_CURVE_H_INCLUDED


