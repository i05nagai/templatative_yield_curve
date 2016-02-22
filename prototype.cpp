
struct tenor {
private:
public:
    typedef double type;

pulbic:
    tenor(const double y, const double m, const double d) 
        : _y(y), _m(m), _d(d)
    {
    }

private:
    const double _y;
    const double _m;
    const double _d;
}

template<typename Rate>
struct market_rate_traits {
    
    Rate::tenor_type tenor(Rate& r) 
    {
        return r.getTenor();
    }
};

struct newton_method {
    newton_method();

    apply(Expression exp)
    {
        //LU decomposition

    }

}

int main(int argc, char const* argv[])
{
    yiedcurve;
    yiedlcurve.getDiscountFactor();
    
    calibrator;

    
    return 0;
}
