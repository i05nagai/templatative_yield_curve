#ifndef AD_TEST_JACOBIAN_MATRIX_TEST_H_INCLUDED
#define AD_TEST_JACOBIAN_MATRIX_TEST_H_INCLUDED

#include <boost/numeric/ublas/matrix.hpp>
#include "ad/dual.h"
#include "ad/helper_macro.h"
#include "ad/helper_function.h"
#include "ad/jacobian_matrix.h"

namespace ad_test {
    namespace ublas = boost::numeric::ublas;
    namespace ad = ddd::ad;

    bool jacobian_matrix_test() {
        std::cout << "---------jacobian_matrix_test start-------" << std::endl;

        //case: dual<V, scalar>
        {
            std::cout << "---start---" << "dual<v, scalar>" << std::endl;
            std::cout << "---end-----" << "dual<v, scalar>" << std::endl;
        }

        //case: dual<V, vector>
        {
            typedef ad::dual<double> dual_type;
            dual_type d(1.0, ublas::vector<double>(2));
            ad::dual_jacobian_matrix_adapter<dual_type> D(d);
            DISPLAY_JACOBIAN_MATRIX(D);
        }

        //case: vector<dual<v, scalar>>
        {

        }

        //case: vector<dual<v, vector>>
        {
            std::cout << "---start---" << "vector<dual<v, vector>>" << std::endl;

            typedef ublas::vector<ad::dual<double> > dual_type;
            dual_type d = ad::make_unit_vector_dual(0.0, 2);
            ad::dual_jacobian_matrix_adapter<dual_type> D(d);
            DISPLAY_JACOBIAN_MATRIX(D);

            std::cout << "---end-----" << "vector<dual<v, vector>>" << std::endl;
        }

        //case: Matrix x Matrix
        {
            std::cout << "---start---" << "Matrix x Matrix" << std::endl;

            std::cout << "---end-----" << "Matrix x Matrix" << std::endl;
        }

        std::cout << "---------jacobian_matrix_test end---------" << std::endl;
        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_JACOBIAN_MATRIX_TEST_H_INCLUDED
