#include <boost/test/unit_test.hpp>
#include <forward_list>
#include <string>
#include <forward_list>
#include "Assembler.h"
#include "Sequence.h"
#include "FixedKSelector.h"

using namespace dnasm;

BOOST_AUTO_TEST_CASE ( input_reading ){
    Assembler dnaAssembler;
    dnaAssembler.readInputFile("in1.txt");
    const std::list<Sequence> unparsedSequences= dnaAssembler.getUnparsedSequences();
    auto it = unparsedSequences.begin();
    BOOST_CHECK_EQUAL( unparsedSequences.size() , 5 );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUAGAATAGUATAGUTAGATUG") );
	BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUAGATAGTTTGAGATGATAG") );
	BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUGUAGUAGUGUATGAUTAG") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("ATGUGATGAUTGAUTAGUATGAUTAG") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("UGUATGAUTAGGUGUAGUAG") );

    dnaAssembler.setOutputFile("out1.txt");
    dnaAssembler.setOutputDotFile("dotout1.txt");
    dnaAssembler.setKSelector(std::unique_ptr<KSelector>(new FixedKSelector()));
    dnaAssembler();
}

BOOST_AUTO_TEST_CASE ( equal_lengt_samples ){
    Assembler dnaAssembler;
    dnaAssembler.readInputFile("in2.txt");
    const std::list<Sequence> unparsedSequences= dnaAssembler.getUnparsedSequences();
    auto it = unparsedSequences.begin();
    BOOST_CHECK_EQUAL( unparsedSequences.size() , 8 );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUAT") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("UATT") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("ATTG") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("TTGA") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("TGAT") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GATA") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("ATAG") );
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("TAGU") );
    dnaAssembler.setOutputFile("out2.txt");
    dnaAssembler.setOutputDotFile("dotout2.txt");
    dnaAssembler.setKSelector(std::unique_ptr<KSelector>(new FixedKSelector(4)));
    dnaAssembler();
}


// EOF