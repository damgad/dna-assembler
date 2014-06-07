
#include <boost/test/unit_test.hpp>

#include <list>
#include "DeBrujinGraph.h"
#include "Generator.h"
#include "Sequence.h"
using namespace dnasm;

BOOST_AUTO_TEST_CASE( test_one ){
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
    std::cout << graph;
    BOOST_CHECK_EQUAL( graph.getEulerPath().toString() , "GUATTGATAGU");

}
BOOST_AUTO_TEST_CASE( test_two ){
	BOOST_CHECK_EQUAL( 0, NULL );
}
// EOF