#ifndef DD_YC_CALIBRATOR_H_INCLUDED
#define DD_YC_CALIBRATOR_H_INCLUDED

namespace dd { namespace yc {

    //vector<dual>
    template <typename F>
    struct differentiate_traits;

    //vector and dual
    template <typename F>
    struct differentiate_traits<ublas::vector_expression<E> > {
    private:
        typedef differentiate_traits<ublas::vector_expression<E> > this_type;
    public:
        typedef ublas::vector_expression<E> expression_type;
    public:
        static result_type apply(const expression_type& e)
        {

        }
    private:
    };
    //dual
    template <typename F>
    struct differentiate_traits<ublas::vector_expression<E> > {
    private:
        typedef differentiate_traits<ublas::vector_expression<E> > this_type;
    public:
        typedef ublas::vector_expression<E> expression_type;
    public:
        static result_type apply(const expression_type& e)
        {

        }
    private:
    };
    
    template <typename F>
    scalar_differentiate_traits<F>::result_type
    differentiate(const dual_expression<F>& f)
    {
        typedef differentiate_traits<F> Tr;
        return Tr::apply(f);
    }

    
    template <typename F>
    vector_differentiate_traits<F>::result_type
    differentiate(const dual_expression<F>& f)
    {
        typedef differentiate_traits<F> Tr;
        return Tr::apply(f);
    }
        

    template <typename F>
    class newton_raphson {
    privatke:
        typedef newton_rapthson<F> this_type;
    public:
        typedef F function_type;
        typedef typename F::result_type function_result_type;
        typedef typename F::value_type value_type;
        typedef value_type result_type;

    public:
        newton_raphson(const std::size_t numberOfTrial)
        : _numberOfTrial(numberOfTrial)
        {
        }

        result_type optimize(
            const function_type& f, 
            const value_type& x0)
        {
            value_type x1 = x0;
            value_type x2;
            function_result_type y = f(x1);
            std::size_t count = 1;

            while(this->isConverge(x1, x2, count))
            {
                x1 = x2;
                x2 = x1 - differentiate_traits::apply(f) * y;
                y = f(x1);
                ++count;
            }
        }

    private:
        bool isConverged(
            const value_type& x1,
            const value_type& x2,
            std::size_t& count)
        {
            return norm(x1, x2) < std::numeric_limits<value_type>::epsilon()
                || count > _numberOfTrial;
        }
        
        std::size_t _numberOfTrial;
    };

    template <typename E, typename M>
    struct calibrator {
    private:
        typedef calibrator<E, M> this_type;
    public:
        typedef F funciton_type;
        typedef M method_type;
    public:
        static result_type apply(
            const function_type& f,
            const method_type& m,
            const value_type& x0)
        {
            return m.optimize(f, x0);
        }
    private:

    };
    
} } // namespace dd { namespace yc {

#endif // #ifndef DD_YC_CALIBRATOR_H_INCLUDED
