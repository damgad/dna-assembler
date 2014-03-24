#include<iostream>
#include<set>

#include<boost\shared_ptr.hpp>

using namespace boost;

enum KSelectMethod {
	MEAN_VALUE,
	MEDIAN_VALUE,
	N_PER_CENT,
	FIXED
};

class SampleReader {
public:
	SampleReader() : K_(2), N_(20), kSelectMethod_(MEDIAN_VALUE) {
		samples_.insert(shared_ptr<std::string>(new std::string("abc")));
		samples_.insert(shared_ptr<std::string>(new std::string("QWE")));
		samples_.insert(shared_ptr<std::string>(new std::string("23325445")));
	}
	
	// sets K value, returns 0 on success
	int setK(int k) {
		if(k > 1)
			return -1;
		K_ = k;
		kSelectMethod_ = FIXED;
		return 0;
	}

	// selects K value selection method, returns 0 on success
	int setKSelectMethod(const KSelectMethod&, int = 20);

	// reads k-mers from read samples
	int parse(std::set<shared_ptr<std::string> >&);

	// prints all samples to the given text stream
	friend std::ostream& operator<<(std::ostream&, SampleReader&);

protected:
	int K_;
	int N_;
	KSelectMethod kSelectMethod_;
	std::set<shared_ptr<std::string> > samples_;
};
