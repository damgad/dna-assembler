#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

#include "Sequence.h"
#include "Generator.h"
#include "Exceptions.h"

Generator::Generator() : correct_(false){
    std::srand(std::time(NULL));
}

void Generator::setInputSequence(Sequence sequence){
    inputSequence_=sequence;
}
void Generator::setOutputFilename(std::string filename){
    outputFilename_=filename;
}

void Generator::readInputSequence(std::string filename){
    std::ifstream inputFile;
    inputFile.open(filename);
    if (!inputFile.good()){
        throw FileNotFoundException("Could not open input sequence file");
    }
    std::string sequenceString;
    getline(inputFile, sequenceString);
    inputSequence_=Sequence(sequenceString);
    inputFile.close();

}

void Generator::randomInputSequence(){ //TODO: remove hardcoded values
    std::string sequenceString("");
    for (int length = 50+rand()%100; length > 0 ; --length){
        switch (rand()%4){
        case 0:
            sequenceString+="A";
            break;
        case 1:
            sequenceString+="G";
            break;
        case 2:
            sequenceString+="T";
            break;
        case 3:
            sequenceString+="C";
            break;
        default:
            break;
        }
    }
    inputSequence_=Sequence(sequenceString);
}

void Generator::setFragmentsLength(int length){
    fragmentsLength_=length;
}

void Generator::setFragmentsNb(int number){
    fragmentsNb_=number;
}

void Generator::setCorectness(bool correct){
    correct_=correct;
}

void Generator::operator()() const{
    std::ofstream outputFile;
    outputFile.open(outputFilename_);
    if (outputFile.good()) {
        generate(outputFile);
    } else {
        generate(std::cout);
    }
    outputFile.close();
}

void Generator::generate(std::ostream & outStream) const{
    int realFragmentsNb = correct_ ? inputSequence_.getLength()-fragmentsLength_ : fragmentsNb_;
    
    std::list<Sequence> fragments;
    for ( int i=0; i<realFragmentsNb ; ++i){
        int offset = correct_ ? i : std::rand()%(inputSequence_.getLength()-fragmentsLength_);
        fragments.push_back(inputSequence_.subsequence(offset,fragmentsLength_));
    }

    //std::random_shuffle(fragments.begin(), fragments.end());

    for_each(fragments.begin(), fragments.end(), [&outStream](Sequence & sequence){ outStream << sequence; });
   
}