#ifndef SHARED_STRING_COMPARATOR_H_
#define SHARED_STRING_COMPARATOR_H_

#include<functional>
#include<boost\shared_ptr.hpp>
#include<string>

typedef boost::shared_ptr<std::string> SharedString;

struct SharedStringComparator : std::less<SharedString> {
	bool operator()(const SharedString &first, const SharedString &second) {
		return (*first) < (*second);
	}
};

struct SharedStringPairComparator : std::less<std::pair<SharedString, SharedString> > {
	bool operator()(const std::pair<SharedString, SharedString> &first, const std::pair<SharedString, SharedString> &second) {
		return *(first.first) < *(second.first) || (*(first.first) == *(second.first) && *(first.second) < *(second.second));
	}
};

#endif // SHARED_STRING_COMPARATOR_H_