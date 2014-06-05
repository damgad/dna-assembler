#include <string>
#include "Sequence.h"

namespace dnasm {

    Sequence::Sequence() : sequence_(){
    }

    Sequence::Sequence(std::string sequence) : sequence_(sequence){
        //TODO: check with alphabet
    }

    int Sequence::operator<(const Sequence& other) const{
	    return getLength()<other.getLength();
    }

    std::forward_list<Sequence> Sequence::getSubsequences(int length) const{
	    if (getLength() < length){
		    return std::forward_list<Sequence>();
	    }
	    std::forward_list<Sequence> output;
	    for (int i = getLength() - length ; i>=0 ; --i ){
		    output.push_front(subsequence(i,length));
	    }
	    return output;
    }


    Sequence Sequence::subsequence(int offset, int length) const{
        return Sequence(sequence_.substr(offset,length));
    }

    int Sequence::getLength() const{
	    return sequence_.size();
    }

    std::ostream& operator<<(std::ostream &outputStream, const Sequence &sequence) {
	    outputStream << sequence.sequence_ << std::endl;
	    return outputStream;
    }

    std::string Sequence::toString() const{
        return sequence_;
    }

}