#ifndef STATISTICS_H
#define STATISTICS_H

#include <cmath>
#include <numeric>

template <typename ForwardIterator>
double GetMean(ForwardIterator begin, ForwardIterator end)
{
    return accumulate(begin, end, 0.0) / distance(begin, end);
}

class StandardDeviationHelper
{
public:
    explicit StandardDeviationHelper(double mean) : mean(mean) {}
    double operator() (double accumulator, double currentValue) const
    {
        const double expr = currentValue - mean;
        return accumulator + expr * expr;
    }

private:
    const double mean;
};

template <typename ForwardIterator>
double GetStandardDeviation(ForwardIterator begin, ForwardIterator end)
{
    const double mean = GetMean(begin, end);
    const double sum = accumulate(begin, end, 0.0, StandardDeviationHelper(mean));
    return sqrt(sum / distance(begin, end));
}

inline bool IsInsertSizeAnormalous(const std::vector<int>& insertSizes, int libMean, int diffThreshold)
{
    int mean = (int)round(GetMean(begin(insertSizes), end(insertSizes)));
    return abs(mean - libMean) >= diffThreshold;
}

#endif // STATISTICS_H
