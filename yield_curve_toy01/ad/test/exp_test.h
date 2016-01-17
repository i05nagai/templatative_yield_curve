#ifndef AD_TEST_EXP_TEST_H_INCLUDED
#define AD_TEST_EXP_TEST_H_INCLUDED
namespace ad_test {
    
    bool exp_test() {
        std::cout << "---------start-------" << std::endl;

        //case: double
        {
            const double x = std::log(1.0);
            const double y = ad::log(x);
            DISPLAY_VAR(y);
        }

        //case: dual(size=1)
        {
            const ad::dual<double> x(std::log(1.0));
            const ad::dual<double> y = ad::log(x);
            DISPLAY_VAR(y);
        }

        //case: dual(size=2)
        {
            const ad::dual<double, 2> x(std::log(1.0));
            const ad::dual<double, 2> y = ad::log(x);
            DISPLAY_VAR(y);
        }

        std::cout << "---------end---------" << std::endl;
        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_EXP_TEST_H_INCLUDED
