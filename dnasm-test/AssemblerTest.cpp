#include <boost/test/unit_test.hpp>
#include <forward_list>
#include <string>
#include <forward_list>
#include "Assembler.h"
#include "Sequence.h"

BOOST_AUTO_TEST_CASE ( input_reading ){
    Assembler dnasm("in1.txt");
    const std::list<Sequence> unparsedSequences= dnasm.getUnparsedSequences();
    auto it = unparsedSequences.begin();
    BOOST_CHECK_EQUAL( unparsedSequences.size() , 5 );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUAGAATAGUATAGUTAGATUG") );
	BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUAGATAGTTTGAGATGATAG") );
	BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUGUAGUAGUGUATGAUTAG") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("ATGUGATGAUTGAUTAGUATGAUTAG") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("UGUATGAUTAGGUGUAGUAG") );
}

// EOF