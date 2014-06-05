#ifndef PERCENTAGE_K_SELECTOR_H
#define PERCENTAGE_K_SELECTOR_H
#include "KSelector.h"

namespace dnasm {
    class PercentageKSelector : public KSelector{
    public:
        PercentageKSelector(int percentage = PercentageKSelector::MEDIAN_PERCENTAGE);
        int calculateK(std::list<Sequence> reads) const;
    private:
        double percentage_;
        static const int MEDIAN_PERCENTAGE = 50;
    };
}

#endif

