#ifndef AD_TEST_TYPE_TRAITS_TEST_H_INCLUDED
#define AD_TEST_TYPE_TRAITS_TEST_H_INCLUDED

#include <boost/numeric/ublas/vector.hpp>
#include "ad/type_traits.h"
#include "ad/dual.h"

namespace ad_test {
    namespace ad = ddd::ad;
    namespace ublas = boost::numeric::ublas;
    bool type_traits_test() {
        std::cout << "---------type_traits start-------" << std::endl;

        //case: is_vector
        {
            if (ad::is_scalar<double>::value) {
                std::cout << "double" << std::endl;
            }
            if (ad::is_scalar<ad::dual<double> >::value) {
                std::cout << "ad::dual<double>" << std::endl;
            }
            if (ad::is_scalar<ublas::vector<double> >::value) {
                std::cout << "ublas::vector<double>" << std::endl;
            }
            if (ad::is_scalar<ublas::vector<ad::dual<double> > >::value) {
                std::cout << "ublas::vector<ad::dual<double> >" << std::endl;
            }
        }

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
            if (ad::is_scalar_dual<double>::value) {
                std::cout << "double" << std::endl;
            }
            if (ad::is_scalar_dual<ad::dual<double> >::value) {
                std::cout << "ad::dual<double>" << std::endl;
            }
            if (ad::is_scalar_dual<ublas::vector<double> >::value) {
                std::cout << "ublas::vector<double>" << std::endl;
            }
            if (ad::is_scalar_dual<ublas::vector<ad::dual<double> > >::value) {
                std::cout << "ublas::vector<ad::dual<double> >" << std::endl;
            }
        }

        //case: is_dual
        {
            if (ad::is_dual<double>::value) {
                std::cout << "double" << std::endl;
            }
            if (ad::is_dual<ad::dual<double> >::value) {
                std::cout << "ad::dual<double>" << std::endl;
            }
            if (ad::is_dual<ublas::vector<double> >::value) {
                std::cout << "ublas::vector<double>" << std::endl;
            }
            if (ad::is_dual<ublas::vector<ad::dual<double> > >::value) {
                std::cout << "ublas::vector<ad::dual<double> >" << std::endl;
            }
        }

        std::cout << "---------type_traits end---------" << std::endl;
        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_TYPE_TRAITS_TEST_H_INCLUDED
