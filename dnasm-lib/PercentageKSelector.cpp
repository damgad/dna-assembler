#include "PercentageKSelector.h"

PercentageKSelector::PercentageKSelector(int percentage) : 
    percentage_(percentage/100.0) {
}

int PercentageKSelector::calculateK(std::list<Sequence> reads) const {
    int lastIndex = (int)std::ceil((1.0-percentage_) * reads.size());
    reads.sort();
    auto it = reads.begin();
    for ( int i=0; i<lastIndex ; ++i){
        ++it;
    }
    return (*it).getLength();
}