#include "MeanKSelector.h"


MeanKSelector::MeanKSelector(){
}

int MeanKSelector::calculateK(std::list<Sequence> reads) const{
    int sum = 0; //TODO: potentially dangerous
    for ( Sequence read : reads ){
        sum+=read.getLength();
    }
    return sum/reads.size();
}