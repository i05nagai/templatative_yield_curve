#ifndef DD_YC_TEST_CURVE_TEST_H_INCLUDED
#define DD_YC_TEST_CURVE_TEST_H_INCLUDED

#include <vector>
#include "yc/curve.h"
#include "yc/interpolator.h"
#include "NumberGenerator.h"

namespace dd { namespace yc_test {
    bool curve_test() 
    {
        detail::NumberGenerator generator(0.0, 10.0);
        std::vector<double> grid(5);
        for (std::size_t i = 0; i < grid.size(); ++i) {
            grid[i] = i;
        }
        std::vector<double> data(5);
        for (std::size_t i = 0; i < data.size(); ++i) {
            data[i] = i + generator();
        }
        typedef std::vector<double> grid_type;
        typedef std::vector<double> data_type;
        {
            typedef yc::linear_interpolation interpolation_type;
            yc::curve<grid_type, data_type, interpolation_type> 
                curve(grid, data);

            double p = grid[0] - 1.0;
            std::cout << p << ":" << curve(p) << std::endl;
            for (std::size_t i = 0; i < grid.size(); ++i) {
                const double p = grid[0] + 0.5 * (i - 1);
                std::cout << p << ":" << curve(p) << std::endl;
            }
            p = grid[grid.size() - 1];
            std::cout << p << ":" << curve(p) << std::endl;
        }

        {
            typedef yc::catmull_rom_spline interpolation_type;
            yc::curve<grid_type, data_type, interpolation_type> 
                curve(grid, data);

            curve(grid[0] - 1.0);
            double p = grid[0] - 1.0;
            std::cout << p << ":" << curve(p) << std::endl;
            for (std::size_t i = 0; i < grid.size() * 2; ++i) {
                const double p = grid[0] + 0.5 * (i - 1);
                std::cout << p << ":" << curve(p) << std::endl;
            }
            p = grid[grid.size() - 1];
            std::cout << p << ":" << curve(p) << std::endl;
        }
        
        return true;
    }
    
} } // namespace dd { namespace yc_test {

#endif // #ifndef DD_YC_TEST_CURVE_TEST_H_INCLUDED

