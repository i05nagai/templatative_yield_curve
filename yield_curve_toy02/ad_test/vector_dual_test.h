#ifndef AD_TEST_VECTOR_DUAL_TEST_H_INCLUDED
#define AD_TEST_VECTOR_DUAL_TEST_H_INCLUDED

namespace ad_test {
    using ad;
    void vector_dual_test()
    {
        vector<dual<double> > a(2);
        dual<double> r = a(0) + a(1) * a(0);

    }

    //vector: size = 1
    void vector_dual_test1() {
        typedef ad::dual<double> value_type;
        //typedef double value_type;
        typedef ad::vector<value_type> domain_type;
        domain_type x(1);
        x(0) = value_type(3.0, 1.0); //bad interface
        //x(0) = value_type(3.0);
        typedef typename func_vector_traits<
            ad::vector<ad::dual<double> > >::result_type result_type;
        const result_type& y = func_vector(x);
        DISPLAY_VAR(y(0).v());
        DISPLAY_VAR(y(0).d());
    }

    //vector: size = 2
    void vector_dual_test2() {
        typedef ad::dual<double> value_type;
        //typedef double value_type;
        typedef ad::vector<value_type> domain_type;
        domain_type x(2);
        x(0) = value_type(3.0, 1.0); //bad interface
        x(1) = value_type(2.0, 1.0); //bad interface
        //x(0) = value_type(3.0);
        typedef typename func_vector_traits<
            ad::vector<ad::dual<double> > >::result_type result_type;
        const result_type& y = func_vector(x);
        DISPLAY_VAR(y(0).v());
        DISPLAY_VAR(y(0).d());
        DISPLAY_VAR(y(1).v());
        DISPLAY_VAR(y(1).d());
    }

    
} // namespace ad_test {

#endif // #ifndef AD_TEST_VECTOR_DUAL_TEST_H_INCLUDED

