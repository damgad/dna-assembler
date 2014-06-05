#ifndef GENERATOR_H
#define GENERATOR_H

#include "Sequence.h"

namespace dnasm {
    class Generator{
    public:

       Generator();

       void setInputSequence(Sequence sequence);
       void readInputSequence(std::string filename);
       void randomInputSequence();
       void setFragmentsLength(int length);
       void setFragmentsNb(int number);
       void setCorectness(bool correct);
       void setOutputFilename(std::string filename);
       void operator()() const;

    private:
        Sequence inputSequence_;
        std::string outputFilename_;
        int fragmentsLength_;
        int fragmentsNb_;
        bool correct_;

        void generate(std::ostream & outStream) const;
    };
}

#endif