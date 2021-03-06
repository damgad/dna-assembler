#ifndef K_SELECTOR
#define K_SELECTOR
#include <list>
#include "Sequence.h"

namespace dnasm {
    class KSelector {
    public:
        virtual ~KSelector() {};
        virtual int calculateK(std::list<Sequence> reads) const = 0;
    };
}

#endif