#include <boost/test/unit_test.hpp>
#include <iostream>
#include <fstream>
#include <forward_list>
#include <string>
#include <boost/test/unit_test.hpp>
#include <forward_list>

#include "Generator.h"
using namespace dnasm;

BOOST_AUTO_TEST_CASE (correct_fromfile_generating){
    Generator generator;
    generator.readInputSequence("in-seq1.txt");
    generator.setCorectness(true);
    generator.setFragmentsLength(6);
    generator.setOutputFilename("genout-seq1-correct6.txt");
    generator();

    std::ifstream output("genout-seq1-correct6.txt");
    std::vector<std::string> generatedSequences;
    while(output.good()){
        std::string sequence;
        output >> sequence;
        generatedSequences.push_back(sequence);
    }
    
    BOOST_CHECK_EQUAL(generatedSequences[0], "GCTAAA");
    BOOST_CHECK_EQUAL(generatedSequences[1], "CTAAAG");
    BOOST_CHECK_EQUAL(generatedSequences[2], "TAAAGT");
    BOOST_CHECK_EQUAL(generatedSequences[3], "AAAGTC");
    BOOST_CHECK_EQUAL(generatedSequences[4], "AAGTCA");
    BOOST_CHECK_EQUAL(generatedSequences[5], "AGTCAG");
    BOOST_CHECK_EQUAL(generatedSequences[6], "GTCAGT");
    BOOST_CHECK_EQUAL(generatedSequences[7], "TCAGTC");
    BOOST_CHECK_EQUAL(generatedSequences[8], "CAGTCT");
    BOOST_CHECK_EQUAL(generatedSequences[9], "AGTCTA");
}
// EOF