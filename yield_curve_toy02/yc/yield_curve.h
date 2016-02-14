#ifndef DD_YC_YIELD_CURVE_H_INCLUDED
#define DD_YC_YIELD_CURVE_H_INCLUDED

namespace dd { namespace yc {
    template <typename T, typename D> 
    class quote {
    private:
        typedef quote this_type;

    public:
        typedef T value_type; 
        typedef D date_type; 

    public:
        quote(const value_type& r, const date_type& d)
        : _r(r), _d(d)
        {
        }

    private:
        value_type _r;
        date_type _d;
    };
} } // namespace dd { namespace yc {

namespace dd { namespace yc {
    template <typename Qs>
    class yield_curve {
    private:
        typedef yield_curve this_type;
    public:
        typedef Qs quotes_type;
        typedef Ds dates_type;

    public:
        yield_curve(quotes_type quotes, 
    private:
        quotes_type _quotes;
        dates_type _dates;
    };
} } // namespace dd { namespace yc {

#endif // #ifndef DD_YC_YIELD_CURVE_H_INCLUDED

