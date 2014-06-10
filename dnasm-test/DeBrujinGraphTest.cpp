#include <boost/test/unit_test.hpp>
#include <list>
#include "DeBrujinGraph.h"
#include "Generator.h"
#include "Sequence.h"
using namespace dnasm;

BOOST_AUTO_TEST_CASE( guat_eulerian1 ){
    std::list<Sequence> reads;
    reads.push_back(Sequence("GUAT"));
    reads.push_back(Sequence("UATT"));
    reads.push_back(Sequence("ATTG"));
    reads.push_back(Sequence("TTGA"));
    reads.push_back(Sequence("TGAT"));
    reads.push_back(Sequence("GATA"));
    reads.push_back(Sequence("ATAG"));
    reads.push_back(Sequence("TAGU"));

    DeBrujinGraph graph(reads);

    BOOST_CHECK( graph.hasEulerPath() );
    BOOST_CHECK_EQUAL( graph.getEulerPath().toString() , "GUATTGATAGU");

}
BOOST_AUTO_TEST_CASE( ab_not_eulerian1 ){
    std::list<Sequence> reads;
    reads.push_back(Sequence("AAAB"));
    reads.push_back(Sequence("AABA"));
    reads.push_back(Sequence("ABAA"));
    reads.push_back(Sequence("BAAB"));
    reads.push_back(Sequence("BAAB"));
    reads.push_back(Sequence("AABA"));
    reads.push_back(Sequence("AABA"));
    reads.push_back(Sequence("ABAB"));

    
    DeBrujinGraph graph(reads);

    BOOST_CHECK( !graph.hasEulerPath() );
}

BOOST_AUTO_TEST_CASE( ab_eulerian1 ){
    std::list<Sequence> reads;
    reads.push_back(Sequence("AAAB"));
    reads.push_back(Sequence("AABA"));
    reads.push_back(Sequence("ABAA"));
    reads.push_back(Sequence("BAAB"));
    reads.push_back(Sequence("AABA"));
    reads.push_back(Sequence("ABAB"));

    
    DeBrujinGraph graph(reads);

    BOOST_CHECK( graph.hasEulerPath() );
    BOOST_CHECK_EQUAL( graph.getEulerPath().toString() , "AAABAABAB");
}
// EOF