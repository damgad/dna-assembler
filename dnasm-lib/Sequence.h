#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <forward_list>

class Sequence {
public:
	explicit Sequence();
	explicit Sequence(std::string sequence);

	friend std::ostream& operator<<(std::ostream&, const Sequence &);

	int operator<(const Sequence& other) const;
	std::forward_list<Sequence> getSubsequences(int length) const;
    Sequence subsequence(int offset, int length) const;
	int getLength() const;
    std::string toString() const;
private: 
	std::string sequence_;
};
#endif SEQUENCE_H
