#ifndef DD_DATE_DAYCOUNTER_H_INCLUDED
#define DD_DATE_DAYCOUNTER_H_INCLUDED

namespace dd { namespace date {
    class DayCounter {
    public:
        double operator()(const Date& start, const Date& end) const;
        boost::shared_ptr<DayCounter> clone() const;
    private:
        virtual double doOperatorParenthesis(
            const Date& start, const Date& end) const = 0;
        virtual DayCounter* doClone() const = 0;
    };
} // namespace dd { namespace date {

#endif // #ifndef DD_DATE_DAYCOUNTER_H_INCLUDED
