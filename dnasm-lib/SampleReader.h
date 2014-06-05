#ifndef SAMPLE_READER_H_
#define SAMPLE_READER_H_

#include<iostream>
#include<set>
#include<unordered_map>
#include<boost\shared_ptr.hpp>
#include<vector>
#include<string>

#include "SharedStringComparator.h"

using namespace boost;
namespace dnasm {

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

	    // reads k-mers from read samples, gets vertex set and edge set
	    typedef std::set<shared_ptr<std::string>, SharedStringComparator> SharedStringSet;
	    typedef std::set<std::pair<shared_ptr<std::string>, shared_ptr<std::string>>, SharedStringPairComparator> SharedStringPairSet;
	    int parse(std::vector<std::string> &, std::set<std::pair<int, int> > &);

    private:
	    // calculates K value for further computation
	    int obtainK();

    protected:
	    int K_;
	    int N_;
	    KSelectMethod kSelectMethod_;
	    std::set<shared_ptr<std::string> > samples_;
    };
}
#endif // SAMPLE_READER_H_