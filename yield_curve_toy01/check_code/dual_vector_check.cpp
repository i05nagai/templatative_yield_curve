#include <iostream>

#include "../ad/dual.h"
#include "../ad/helper_macro.h"

int main(int argc, char const* argv[])
{
    {
        ad::dual_vector<double> x(2, 2);
        DISPLAY_VAR(x(0));
        DISPLAY_VAR(x(1));

        ad::dual_vector<double> y1 = x * 2.0;
        DISPLAY_VAR(y1(0));
        DISPLAY_VAR(y1(1));
        ad::dual_vector<double> y2 = 2.0 * x;
        DISPLAY_VAR(y2(0));
        DISPLAY_VAR(y2(1));

        ad::dual_vector<double> y3 = x / 2.0;
        DISPLAY_VAR(y3(0));
        DISPLAY_VAR(y3(1));
    }

    {
        ad::dual_vector<ad::dual<double> > x(2);
        x(0) = ad::dual<double>(2.0, 0u);
        x(1) = ad::dual<double>(2.0, 0u);
        ad::dual<double> c(1.0, 0u);

        ad::dual_vector<ad::dual<double> > z = c * x;
        DISPLAY_DUAL(z(0));
        DISPLAY_DUAL(z(1));
    }

    return 0;
}
