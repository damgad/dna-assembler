#include "SampleReader.h"

#include<vector>
#include<algorithm>

std::ostream& operator<<(std::ostream &output_stream, SampleReader &reader) {
	std::set<shared_ptr<std::string> >::const_iterator it;
	for(it = reader.samples_.begin(); it != reader.samples_.end(); ++it)
		output_stream << (**it).c_str() << '\n';
	output_stream << std::flush;
	return output_stream;
}

int SampleReader::setKSelectMethod(const KSelectMethod &kSelectMethod, int N) {
	switch(kSelectMethod) {
	case N_PER_CENT:
		if(N >= 0 && N < 100)
			N_ = N;
		else
			return -1;
		// no break
	case MEAN_VALUE:
		// no break
	case MEDIAN_VALUE:
			kSelectMethod_ = kSelectMethod;
		break;
	case FIXED:
		// no break
	default:
		return -1;
	}
	return 0;
}

int SampleReader::parse(std::set<shared_ptr<std::string> > &k_mers) {
	if(samples_.size() == 0)
		return -1;

	// obtain k value
	if(kSelectMethod_ == MEAN_VALUE) {
		int length = 0;
		std::set<shared_ptr<std::string> >::const_iterator it;
		for(it = samples_.begin(); it != samples_.end(); ++it)
			length += (*it)->size();
		K_ = length / samples_.size();
	} else if(kSelectMethod_ == MEDIAN_VALUE) {
		std::vector<shared_ptr<std::string> > samples(samples_.size());
		std::sort(samples.begin(), samples.end());
		if(samples.size() % 2 == 0)
			K_ = (samples[samples.size() / 2]->size() + samples[samples.size() / 2 - 1]->size()) / 2;
		else 
			K_ = samples[samples.size() / 2]->size();
	} else if(kSelectMethod_ == N_PER_CENT) {
		std::vector<shared_ptr<std::string> > samples(samples_.size());
		std::sort(samples.begin(), samples.end());
		if(N_ == 0)
			K_ = samples[0]->size();
		else
			K_ = samples[samples_.size() * 100 / N_]->size();
	} // else k is fixed

	// generate k-mers

}
