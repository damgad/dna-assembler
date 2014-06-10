#include <boost/test/unit_test.hpp>
#include <iostream>
#include <fstream>
#include <forward_list>
#include <string>
#include <forward_list>
#include "Assembler.h"
#include "Sequence.h"
#include "FixedKSelector.h"
#include "PercentageKSelector.h"
using namespace dnasm;

BOOST_AUTO_TEST_CASE ( input_file_reading ){
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
    dnaAssembler.setKSelector(std::unique_ptr<KSelector>(new FixedKSelector(4)));
    dnaAssembler();
    std::ifstream output("out2.txt");
    std::string outputSequence;
    if(output.good()){
        output >> outputSequence;
    }
    BOOST_CHECK_EQUAL( outputSequence , "GUATTGATAGU");

}


BOOST_AUTO_TEST_CASE ( assembling_test ){
    Assembler dnaAssembler;
    dnaAssembler.readInputFile("in3.txt");
    const std::list<Sequence> unparsedSequences= dnaAssembler.getUnparsedSequences();
    BOOST_CHECK_EQUAL( unparsedSequences.size() , 19 );
    dnaAssembler.setOutputFile("out3.txt");
    dnaAssembler.setKSelector(std::unique_ptr<KSelector>(new PercentageKSelector()));
    dnaAssembler();

    std::ifstream output("out3.txt");
    std::string outputSequence;
    if(output.good()){
        output >> outputSequence;
    }
    BOOST_CHECK_EQUAL( outputSequence , "GUATAGUGUGUGUAGUAGUGUA");
}





// EOF