#ifndef AD_TEST_TYPE_TRAITS_TEST_H_INCLUDED
#define AD_TEST_TYPE_TRAITS_TEST_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include "ad/type_traits.h"
#include "ad/dual.h"

namespace ad_test {
    namespace ublas = boost::numeric::ublas;
    bool type_traits_test() {
        std::cout << "---------type_traits start-------" << std::endl;

        //case: is_vector
        {
            
        }

        //case: is_vector_dual
        {
            if (ad::is_vector_dual<double>::value) {
                std::cout << "double" << std::endl;
            }
            if (ad::is_vector_dual<ad::dual<double> >::value) {
                std::cout << "ad::dual<double>" << std::endl;
            }
            if (ad::is_vector_dual<ublas::vector<double> >::value) {
                std::cout << "ublas::vector<double>" << std::endl;
            }
            if (ad::is_vector_dual<ublas::vector<ad::dual<double> > >::value) {
                std::cout << "ublas::vector<ad::dual<double> >" << std::endl;
            }
        }

        //case: is_scalar_dual
        {
        }

        //case: is_dual
        {
        }

        std::cout << "---------type_traits end---------" << std::endl;
        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_TYPE_TRAITS_TEST_H_INCLUDED
