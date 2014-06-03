#ifndef MEAN_K_SELECTOR_H
#define MEAN_K_SELECTOR_H
#include <list>
#include "KSelector.h"
class MeanKSelector : public KSelector {
public:
    MeanKSelector();
    int calculateK(std::list<Sequence> reads) const;
};

#endif