#include <string>
#include "Sequence.h"

Sequence::Sequence(std::string sequence) : sequence_(sequence){
}

Sequence::~Sequence(){
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
		output.push_front(Sequence(sequence_.substr(i,length)));
	}
	return output;
}

int Sequence::getLength() const{
	return sequence_.size();
}

std::ostream& operator<<(std::ostream &outputStream, const Sequence &sequence) {
	//outputStream << sequence.sequence_;
	return outputStream;
}