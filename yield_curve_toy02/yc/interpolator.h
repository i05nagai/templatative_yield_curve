#ifndef DD_YC_INTERPOLATION_H_INCLUDED
#define DD_YC_INTERPOLATION_H_INCLUDED
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace dd { namespace yc {
    namespace ublas = boost::numeric::ublas;

    template <typename I>
    struct interpolator {
    private:
        typedef interpolator<I> this_type;
    public:
        typedef I interpolator_type;
    public:
        template <typename G, typename V, typename P>
        static typename V::value_type apply(
            const G& grid, 
            const V& data, 
            const P& point)
        {
            return interpolator_type::apply(grid, data, point);
        }
    };

    struct linear_interpolation {
    private:
            typedef linear_interpolation this_type;
    public:
        ///
        template <typename G, typename V, typename P>
        static typename V::value_type apply(
            const G& grid, 
            const V& data, 
            const P& point)
        {
            // point <= first -> constant extrapolation
            if (point < grid[0]) {
                return data[0];
            }
            
            // ith < point <= jth -> linear interpolation
            for (std::size_t i = 1; i < grid.size(); ++i) {
                if (point < grid[i]) {
                    return (point - grid[i - 1]) / (grid[i] - grid[i - 1]) 
                        * (data[i] - data[i - 1]) + data[i - 1];
                }
            }

            // last < point -> constant extrapolation
            return data[grid.size() - 1];
        }

    };

    struct catmull_rom_spline {
    private:
            typedef catmull_rom_spline this_type;
    public:
        ///
        template <typename G, typename V, typename P>
        static typename V::value_type apply(
            const G& grid, 
            const V& data, 
            const P& point)
        {
            // point <= first -> constant extrapolation
            if (point < grid[0]) {
                extrapolateLeft(grid, data, point);
            }
            
            // ith < point <= jth -> linear interpolation
            for (std::size_t i = 1; i < grid.size(); ++i) {
                if (point < grid[i]) {
                    return interpolate(grid, data, point, i);
                }
            }

            // last < point -> constant extrapolation
            return extrapolateRight(grid, data, point);
        }

    private:
        template <typename G, typename V, typename P>
        static typename V::value_type interpolate(
            const G& grid, 
            const V& data, 
            const P& point,
            const std::size_t i)
        {
            typedef typename V::value_type value_type;
            const P h1 = grid[i - 1] - grid[i - 2];
            const P h2 = grid[i] - grid[i - 1]; 
            const P h3 = grid[i + 1] - grid[i]; 
            const P delta = (point - grid[i - 1]) / h2;
            const P alpha = h2 / (h2 + h1);
            const P beta = h2 / (h3 + h2);
            ublas::vector<value_type> D(4);
            ublas::matrix<value_type> A(4, 4);
            ublas::vector<value_type> Y(4);

            D(0) = std::pow(delta, 3);
            D(1) = std::pow(delta, 2);
            D(2) = std::pow(delta, 1);
            D(3) = 1.0;
            
            A(0, 0) = -alpha;
            A(0, 1) = 2.0 - beta;
            A(0, 2) = -2.0 + alpha;
            A(0, 3) = beta;
            A(1, 0) = 2.0 * alpha;
            A(1, 1) = beta - 3.0;
            A(1, 2) = 3.0 - 2.0 * alpha;
            A(1, 3) = -beta;
            A(2, 0) = -alpha;
            A(2, 1) = 0.0;
            A(2, 2) = alpha;
            A(2, 3) = 0.0;
            A(3, 0) = 0.0;
            A(3, 1) = 1.0;
            A(3, 2) = 0.0;
            A(3, 3) = 0.0;

            Y(0) = data[i - 2];
            Y(1) = data[i - 1];
            Y(2) = data[i];
            Y(3) = data[i + 1];

            return ublas::inner_prod(ublas::prod(D, A), Y);
        }

        
        /**
         * @brief calculate left side extrapolation.
         *
         * @tparam G grid_type
         * @tparam V type of values on grids.
         * @tparam P type of point to be extrapolated.
         * @param grid grids.
         * @param data values on grid.
         * @param point point to be extrapolated.
         *
         * @return extrapolated value.
         */
        template <typename G, typename V, typename P>
        static typename V::value_type extrapolateLeft(
            const G& grid, 
            const V& data, 
            const P& point)
        {
            const std::size_t i = 1;
            typedef typename V::value_type value_type;
            const P h2 = grid[i] - grid[i - 1]; 
            const P h3 = grid[i + 1] - grid[i]; 
            const P delta = (point - grid[i - 1]) / h2;
            const P beta = h2 / (h3 + h2);
            //size can be 3.
            ublas::vector<value_type> D(4);
            ublas::matrix<value_type> A(4, 4);
            ublas::vector<value_type> Y(4);

            D(0) = std::pow(delta, 3);
            D(1) = std::pow(delta, 2);
            D(2) = std::pow(delta, 1);
            D(3) = 1.0;

            A(0, 0) = 0.0;
            A(0, 1) = 1.0 - beta;
            A(0, 2) = -1.0;
            A(0, 3) = -beta;
            A(1, 0) = 0.0;
            A(1, 1) = -1.0 + beta;
            A(1, 2) = 1.0;
            A(1, 3) = -beta;
            A(2, 0) = 0.0;
            A(2, 1) = -1.0;
            A(2, 2) = 1.0;
            A(2, 3) = 0.0;
            A(3, 0) = 0.0;
            A(3, 1) = 1.0;
            A(3, 2) = 0.0;
            A(3, 3) = 0.0;

            Y(0) = 0.0;
            Y(1) = data[i - 1];
            Y(2) = data[i];
            Y(3) = data[i + 1];

            return ublas::inner_prod(ublas::prod(D, A), Y);
        }

        template <typename G, typename V, typename P>
        static typename V::value_type extrapolateRight(
            const G& grid, 
            const V& data, 
            const P& point)
        {
            const std::size_t i = grid.size() - 1;
            typedef typename V::value_type value_type;
            const P h1 = grid[i - 1] - grid[i - 2];
            const P h2 = grid[i] - grid[i - 1]; 
            const P delta = (point - grid[i - 1]) / h2;
            const P alpha = h2 / (h2 + h1);
            //size can be 3.
            ublas::vector<value_type> D(4);
            ublas::matrix<value_type> A(4, 4);
            ublas::vector<value_type> Y(4);

            D(0) = std::pow(delta, 3);
            D(1) = std::pow(delta, 2);
            D(2) = std::pow(delta, 1);
            D(3) = 1.0;

            A(0, 0) = -alpha;
            A(0, 1) = 1.0;
            A(0, 2) = -1.0+alpha;
            A(0, 3) = 0.0;
            A(1, 0) = 2.0 * alpha;
            A(1, 1) = -2.0;
            A(1, 2) = 2.0 - 2.0 * alpha;
            A(1, 3) = 0.0;
            A(2, 0) = -alpha;
            A(2, 1) = 0.0;
            A(2, 2) = alpha;
            A(2, 3) = 0.0;
            A(3, 0) = 0.0;
            A(3, 1) = 1.0;
            A(3, 2) = 0.0;
            A(3, 3) = 0.0;

            Y(0) = data[i - 2];
            Y(1) = data[i - 1];
            Y(2) = data[i];
            Y(3) = 0.0;

            return ublas::inner_prod(ublas::prod(D, A), Y);
        }
        
    };
    
} } // namespace dd { namespace yc {

#endif // #ifndef DD_YC_INTERPOLATION_H_INCLUDED
