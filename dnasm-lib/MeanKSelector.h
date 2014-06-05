#ifndef MEAN_K_SELECTOR_H
#define MEAN_K_SELECTOR_H
#include <list>
#include "KSelector.h"

namespace dnasm {
    class MeanKSelector : public KSelector {
    public:
        MeanKSelector();
        int calculateK(std::list<Sequence> reads) const;
    };
}

#endif