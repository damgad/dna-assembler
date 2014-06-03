#ifndef ASSEMBLER_H 
#define ASSEMBLER_H
#include <list>
#include "Sequence.h"
#include "KSelector.h"
class Assembler{
public:
    Assembler(const std::string & filenameIn);
    
    void setKSelector(std::unique_ptr<KSelector> kSelector);
    void setOutputFile(const std::string & filename);
    void setOutputDotFile(const std::string & filename);
    Sequence operator()() const;
    const std::list<Sequence>& getUnparsedSequences() const;

private:
    std::list<Sequence> unparsedInputSequences_;
    int k_;
    std::string filenameOut_;
    std::string filenameDotOut_;
    std::unique_ptr<KSelector>  kSelectorPtr_;
    void readInputFile(const std::string & filename);
};

#endif