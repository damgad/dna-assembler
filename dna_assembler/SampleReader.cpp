#include "SampleReader.h"

#include<string>
#include<vector>
#include<algorithm>

SampleReader::SampleReader(std::istream &in_stream) : K_(5), N_(20), kSelectMethod_(FIXED) {
	shared_ptr<std::string> string_ptr(new std::string());
	in_stream >> *string_ptr;
	while(in_stream) {
		if(string_ptr->length() > 0) {
			std::string::const_iterator it = string_ptr->begin();
			while(it != string_ptr->end()) {
				if(*it != 'G' && *it != 'C' && *it != 'A' && *it != 'T')
					break;
				++it;
			}
			if(it == string_ptr->end())
				samples_.insert(string_ptr);
		}

		string_ptr.reset(new std::string());
		in_stream >> *string_ptr;
	}
}

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
			// no break, should not be passed to this function(instead use setK(int) function)
		default:
			return -1;
	}
	return 0;
}

int SampleReader::obtainK() {
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
		std::vector<shared_ptr<std::string> > samples(samples_.begin(), samples_.end());
		std::sort(samples.begin(), samples.end(), [](const shared_ptr<std::string> &a, const shared_ptr<std::string> &b){ return a->size() < b->size(); });
		if(samples.size() % 2 == 0)
			K_ = (samples[samples.size() / 2]->size() + samples[samples.size() / 2 - 1]->size()) / 2;
		else
			K_ = samples[samples.size() / 2]->size();
	} else if(kSelectMethod_ == N_PER_CENT) {
		std::vector<shared_ptr<std::string> > samples(samples_.begin(), samples_.end());
		std::sort(samples.begin(), samples.end(), [](const shared_ptr<std::string> &a, const shared_ptr<std::string> &b){ return a->size() < b->size(); });
		if(N_ == 0)
			K_ = samples[0]->size();
		else
			K_ = samples[samples.size() * N_ / 100]->size();
	} // else k is fixed
	return 0;
}

int SampleReader::parse(std::set<shared_ptr<std::string> > &k_mers) {
	if(obtainK() != 0)
		return -1;

	k_mers.clear();
	for(std::set<shared_ptr<std::string> >::const_iterator it = samples_.begin(); it != samples_.end(); ++it) {
		for(int i = 0; i + K_ <= static_cast<int>((*it)->length()); ++i) {
			k_mers.insert(shared_ptr<std::string>(new std::string((*it)->substr(i, K_))));
		}
	}
	
	return 0;
}
