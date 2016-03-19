#ifndef AD_TEST_INVERT_TEST_H_INCLUDED
#define AD_TEST_INVERT_TEST_H_INCLUDED

#include "ad/dual.h"
#include "ad/function.h"
#include "ad/vector.h"
#include "ad/helper_macro.h"
#include <boost/numeric/ublas/matrix.hpp>

namespace ad_test {
    namespace ublas = boost::numeric::ublas;
    bool invert_test() {
        std::cout << "---------inver_test start-------" << std::endl;

        //case: matrix
        {
            ublas::matrix<double> A(2, 2);
            A(0, 0) = 3.242;
            A(1, 1) = 324.343242;
            ublas::matrix<double> B = ad::invert(A);
            ublas::matrix<double> C = ublas::prod(A, B);
            DISPLAY_MATRIX_INFOS(B);
            DISPLAY_MATRIX_INFOS(C);
        }

        //error case: matrix must be square
        {
            ublas::matrix<double> A(2, 1);
            A(0, 0) = 3.242;
            //ublas::matrix<double> B = ad::invert(A);
            //ublas::matrix<double> C = ublas::prod(A, B);
            //DISPLAY_MATRIX_INFOS(B);
            //DISPLAY_MATRIX_INFOS(C);
        }

        std::cout << "---------invert_test end---------" << std::endl;
        return true;
    }
} // namespace ad_test {

#endif // #ifndef AD_TEST_INVERT_TEST_H_INCLUDED
