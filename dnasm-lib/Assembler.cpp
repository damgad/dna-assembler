#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include "Assembler.h"
#include "Exceptions.h"
#include "DeBrujinGraph.h"

namespace dnasm {
    void Assembler::readInputStream(std::istream & stream){
        std::string read;
        while(std::getline(stream, read) && !read.empty()){
            unparsedInputSequences_.push_back(Sequence(read)); //TODO: wrong file handling
        }
    }

    void Assembler::readInputFile(const std::string & filename){
        std::ifstream sequencesStream(filename, std::ifstream::in);
        if(!sequencesStream.is_open()){
            throw FileNotFoundException(std::string("Unable to open file: ") + filename);
        }
        readInputStream(sequencesStream);
        sequencesStream.close();
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

    void Assembler::operator()() const{
        int k = kSelectorPtr_->calculateK(unparsedInputSequences_);
        std::list<Sequence> parsedInputSequences;
        std::for_each(unparsedInputSequences_.begin(), unparsedInputSequences_.end(), 
            [&parsedInputSequences,k](Sequence s){ 
                std::forward_list<Sequence> subsequences = s.getSubsequences(k);
                parsedInputSequences.insert(parsedInputSequences.begin(),subsequences.begin(), subsequences.end());
        });
        DeBrujinGraph graph(parsedInputSequences);
        if(!filenameDotOut_.empty()){
        std::ofstream dotFileStream(filenameDotOut_);
        if(!dotFileStream.good()){
            throw FileNotFoundException(std::string("Unable to open file: ") + filenameDotOut_ + " to write");
        }
        dotFileStream << graph;
        dotFileStream.close();
        }
        if (graph.hasEulerPath()){
            Sequence assembledSequence = graph.getEulerPath();
            if(filenameOut_.empty()){
                std::cout << assembledSequence;
                return;
            }
            std::ofstream outFileStream(filenameOut_);
            if(!outFileStream.good()){
                throw FileNotFoundException(std::string("Unable to open file: ") + filenameOut_ + " to write");
            }
            outFileStream << assembledSequence;
            outFileStream.close();
        } else {
            std::cerr << "Graph does not have Eulerian path.";
        }
    }
}