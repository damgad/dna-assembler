#ifndef FIXED_K_SELECTOR_H
#define FIXED_K_SELECTOR_H

#include "KSelector.h"

namespace dnasm {
    class FixedKSelector : public KSelector {

    public:
        FixedKSelector(int k = FixedKSelector::DEFAULT_K);
        int calculateK(std::list<Sequence> reads) const;
    private:
        int k_;
        static const int DEFAULT_K = 5;
    };
}
#endif