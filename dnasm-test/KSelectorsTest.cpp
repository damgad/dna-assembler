#include <boost/test/unit_test.hpp>
#include <list> 
#include "Sequence.h"
#include "FixedKSelector.h"
#include "MeanKSelector.h"
#include "PercentageKSelector.h"

BOOST_AUTO_TEST_CASE ( fixed_selecting ){
    FixedKSelector fixedSelector(18);
    BOOST_CHECK_EQUAL( fixedSelector.calculateK(std::list<Sequence>()), 18 );
}

BOOST_AUTO_TEST_CASE ( mean_selecting ){
    MeanKSelector meanSelector;
    std::list<Sequence> reads;
    reads.push_back(Sequence("TAGUTAGAUTGU"));
    reads.push_back(Sequence("GUATAGUAGATAGAUT"));
    reads.push_back(Sequence("GUAGAUTAGUTTAGAGAUT"));
    reads.push_back(Sequence("AUTGUTGUA"));
    reads.push_back(Sequence("GUATAGTAUTAAUAT"));
    reads.push_back(Sequence("TAGUTGUAAGAT"));
    reads.push_back(Sequence("GUATAGAGAUUT"));
    reads.push_back(Sequence("GUATAUTUT"));
    BOOST_CHECK_EQUAL( meanSelector.calculateK(reads), 13 );
}

BOOST_AUTO_TEST_CASE ( percentage_selecting ){
    PercentageKSelector medianSelector;
    PercentageKSelector twentyPercentageSelector(20);
    std::list<Sequence> reads;
    reads.push_back(Sequence("TUATAUTGUAGAGUATGTAUAAGAAG"));
    reads.push_back(Sequence("GUA"));
    reads.push_back(Sequence("GUAGUATGUAGAAGTAGTAUGUAUAGAAU"));
    reads.push_back(Sequence("TAGU"));
    reads.push_back(Sequence("UATUTAUTUAGAUTAAGTAUGAUAGAAT"));
    reads.push_back(Sequence("TUA"));
    reads.push_back(Sequence("TU"));
    reads.push_back(Sequence("TAUUATUTAAGGUATUATGUUGAAT"));
    reads.push_back(Sequence("TAU"));
    reads.push_back(Sequence("GAT"));
    BOOST_CHECK_EQUAL( medianSelector.calculateK(reads), 4 );
    BOOST_CHECK_EQUAL( twentyPercentageSelector.calculateK(reads), 28 );
}

// EOF