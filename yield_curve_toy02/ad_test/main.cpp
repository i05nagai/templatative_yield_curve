#include <cstddef>

#include "ad_test/exp_test.h"
#include "ad_test/log_test.h"
#include "ad_test/expression_template_test.h"
//#include "ad_test/automatic_differentiation_test.h"
#include "ad_test/dual_test.h"


int main(int argc, char const* argv[])
{
    ad_test::exp_test();
    ad_test::log_test();
    ad_test::dual_test();
    ad_test::expression_template_test();

//    ad_test::automatic_differentiation_test();

    return 0;
}

