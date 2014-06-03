#include <boost/test/unit_test.hpp>
#include <forward_list>
#include <string>
#include "Sequence.h"

BOOST_AUTO_TEST_CASE( sequence_construction ){
	Sequence sequence = Sequence(std::string("GUAGTA"));
	std::forward_list<Sequence> subSequences = sequence.getSubsequences(4);

	auto it = subSequences.begin();
    BOOST_CHECK_EQUAL( (*it++).toString(), std::string("GUAG") );
	BOOST_CHECK_EQUAL( (*it++).toString(), std::string("UAGT") );
	BOOST_CHECK_EQUAL( (*it++).toString(), std::string("AGTA") );
	BOOST_CHECK( !it._Ptr );
}
BOOST_AUTO_TEST_CASE( constructors_test ){
	BOOST_CHECK_EQUAL( 0, NULL );
}
// EOF