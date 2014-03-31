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
	SampleReader(std::istream& = std::cin);
	
	// sets K value, returns 0 on success
	int setK(int k) {
		if(k <= 1)
			return -1;

		K_ = k;
		kSelectMethod_ = FIXED;
		return 0;
	}

	// prints out all read samples to the given output stream
	friend std::ostream& operator<<(std::ostream&, SampleReader&);

	// chooses K value selection method, returns 0 on success
	int setKSelectMethod(const KSelectMethod&, int = 20);

	// reads k-mers from read samples
	int parse(std::set<shared_ptr<std::string> >&);

private:
	// calculates K value for further computation
	int obtainK();

protected:
	int K_;
	int N_;
	KSelectMethod kSelectMethod_;
	std::set<shared_ptr<std::string> > samples_;

private:
	class StringComparator {
		bool operator()(const std::string &a, const std::string &b){
			return a.size() < b.size();
		}
	};
};
