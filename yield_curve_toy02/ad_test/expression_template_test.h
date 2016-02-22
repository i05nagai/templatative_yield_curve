#ifndef AD_TEST_EXPRESSION_TEMPLATE_TEST_H_INCLUDED
#define AD_TEST_EXPRESSION_TEMPLATE_TEST_H_INCLUDED

namespace ad_test {
    namespace ublas = boost::numeric::ublas;
    bool expression_template_test()
    {
        std::cout << "---------start-------" << std::endl;

        /* expression template */
        ublas::vector<double> v1(10);
        ublas::vector<double> v2(10);
        ublas::vector<double> v3(10);
        for (std::size_t i = 0; i < v1.size(); ++i) {
            v1(i) = i * 0.1;
            v2(i) = i * 0.2;
            v3(i) = i * 0.3;
        }

        {
            ublas::vector<double> v4 = v1 + ad::log(ad::exp(v2)) + (-v3);
            DISPLAY_VECTOR_INFOS(v1);
            DISPLAY_VECTOR_INFOS(v2);
            DISPLAY_VECTOR_INFOS(v3);
            DISPLAY_VECTOR_INFOS(v4);
        }
        std::cout << "---------end--------" << std::endl;

        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_EXPRESSION_TEMPLATE_TEST_H_INCLUDED

