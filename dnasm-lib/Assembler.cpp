#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include "Assembler.h"
#include "Exceptions.h"

Assembler::Assembler(const std::string & filenameIn){
    readInputFile(filenameIn);
}

void Assembler::readInputFile(const std::string & filename){
    std::ifstream sequencesStream(filename, std::ifstream::in);
    if(!sequencesStream.is_open()){
        throw FileNotFoundException(std::string("Unable to open file: ") + filename);
    }
    std::string line;
    while(std::getline(sequencesStream, line)){
        unparsedInputSequences_.push_back(Sequence(line)); //TODO: wrong file handling
    }
}

const std::list<Sequence>& Assembler::getUnparsedSequences() const{
    return unparsedInputSequences_;
}

void Assembler::setKSelector(std::unique_ptr<KSelector> kSelector){
    kSelectorPtr_=std::move(kSelector);
}
void Assembler::setOutputFile(const std::string & filename){
    filenameOut_=filename;
}
void Assembler::setOutputDotFile(const std::string & filename){
    filenameDotOut_=filename;
}

Sequence Assembler::operator()() const{
    int k = kSelectorPtr_->calculateK(unparsedInputSequences_);
    std::list<Sequence> parsedInputSequences;
    std::for_each(unparsedInputSequences_.begin(), unparsedInputSequences_.end(), 
        [&parsedInputSequences,k](Sequence s){ 
            std::forward_list<Sequence> subsequences = s.getSubsequences(k);
            parsedInputSequences.insert(parsedInputSequences.begin(),subsequences.begin(), subsequences.end());
    });

    return Sequence("AGA");
}