#include "FixedKSelector.h"

FixedKSelector::FixedKSelector(int k) :  k_(k) {
} 

int FixedKSelector::calculateK(std::list<Sequence> reads) const { 
    return k_; 
}