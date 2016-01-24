#ifndef YC_DATE_DAYCOUNTER_H_INCLUDED
#define YC_DATE_DAYCOUNTER_H_INCLUDED

namespace yc { namespace date {
    class DayCounter {
    public:
        double operator()(const Date& start, const Date& end) const;
        boost::shared_ptr<DayCounter> clone() const;
    private:
        virtual double doOperatorParenthesis(
            const Date& start, const Date& end) const = 0;
        virtual DayCounter* doClone() const = 0;
    };
} // namespace yc { namespace date {

#endif // #ifndef YC_DATE_DAYCOUNTER_H_INCLUDED
