#ifndef DDD_DATE_DAYCOUNTER_H_INCLUDED
#define DDD_DATE_DAYCOUNTER_H_INCLUDED

namespace ddd { namespace date {
    class DayCounter {
    public:
        double operator()(const Date& start, const Date& end) const;
        boost::shared_ptr<DayCounter> clone() const;
    private:
        virtual double doOperatorParenthesis(
            const Date& start, const Date& end) const = 0;
        virtual DayCounter* doClone() const = 0;
    };
} // namespace ddd { namespace date {

#endif // #ifndef DDD_DATE_DAYCOUNTER_H_INCLUDED
