

dual<double> f(const dual<double>& x)
{
    return x * x + x;
} 

int main(int argc, char const* argv[])
{
    {
        dual<double> c; //=c(0.0)=c(0.0, 0.0);
        dual<double> x1(2.0, 1.0); 
        dual<double> x2(1.0, 1.0);
        dual<double> y1 = x2 * x1 + x2; //error
        dual<double> y2 = f(x1); //y2=
        dual<double> y3 = f(x2); //y3=
        dual<double> y4 = f(y3); //y4=
    }

    {
        dual<double> c;
        vector<dual<double> > x(2);
        x[0] = 2.0; //TODO: x[0] = dual<double>(2.0, 1.0)
        x[1] = 1.0; //TODO: x[1] = dual<double>(1.0, 1.0)
        vector<dual<double> > y(3);
        y[0] = 1.0; //TODO: y[0] = dual<double>(1.0, 1.0)
        y[1] = 2.0; //TODO: y[1] = dual<double>(2.0, 1.0)
        y[2] = 3.0; //TODO: y[2] = dual<double>(3.0, 1.0)
        dual<double> z1 = x[0] * c + x[1]; //OK
        vector<dual<double> > z2(2); 
        z2[0] = x[0] * y[1]; //TODO
        z2[1] = x[1] * y[2]; //TODO
        dual<double> z3 = f(y);//OK
        vector<dual<double> > z4 = f(x); //OK
        vector<dual<double> > z5 = f(y); //OK
    }
    
    return 0;
}

