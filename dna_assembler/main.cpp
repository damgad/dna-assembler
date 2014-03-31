#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#include<boost\program_options.hpp>

#include "SampleReader.h"

using namespace boost::program_options;

void atExit() {
	std::cout << "Press any key to continue.." << std::endl;
	getchar();
}

int main(int argc, char **argv) {

	#ifdef _DEBUG
	atexit(atExit);
	#endif // _DEBUG

	bool sample_generator_mode = false;

	// define program options
	options_description desc("Allowed options:");
	desc.add_options()
		("help,h", "display available options")
		("k,k", value<int>(), "k-mer length(default is 5)")
		("K,K", value<std::string>(), "k-mer length selection mode:\n'A' - mean sample length\n'M' - median sample length\n N - take N% of the longest samples")
		("input-file,i", value<std::string>(), "input file for the program(by default data is read from standard input)")
		("output-file,o", value<std::string>(), "output file for data(must not exist, by default data is written to standard output)")
		("d,d", value<std::string>(), "output file for a DOT format file, representing De Bruijn graph")
		("r,r", bool_switch(&sample_generator_mode), "sample generator mode")
		("s,s", value<std::string>(), "input sequence for sample generator mode")
		("l,l", value<int>(), "sample length for sample generator mode")
		("n,n", value<int>(), "sample count for sample generator mode")
		("c,c", "force sample generator mode to generate samples for a consistent Euler graph")
		;

	// parse program options
	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);

	// handle program options
	vm.notify();

	// display help
	if(vm.count("help")) {
		std::cout << desc << std::endl;
		return 0;
	}

	shared_ptr<SampleReader> sample_reader(0);
	// open input file for reading
	if(vm.count("input-file")) {
		std::string input_file_name = vm["input-file"].as<std::string>();
		std::ifstream input_file_stream(input_file_name, std::ifstream::in);
		if(input_file_stream == 0) {
			std::cerr << "Could not open file \"" << input_file_name << "\" for reading." << std::endl;
			return 0;
		}
		sample_reader.reset(new SampleReader(input_file_stream));
	} else {
		sample_reader.reset(new SampleReader());
	}

	// parse k and K parameters
	if(vm.count("k")) {
		int k = -1;
		k = vm["k"].as<int>();
		if(sample_reader->setK(k) != 0) {
			std::cerr << "Invalid 'k' parameter value: " << k << "." << std::endl;
			return 0;
		}
	} else if(vm.count("K")) {
		std::string K(vm["K"].as<std::string>());
		if(K == "A") {
			sample_reader->setKSelectMethod(KSelectMethod::MEAN_VALUE);
		} else if(K == "M") {
			sample_reader->setKSelectMethod(KSelectMethod::MEDIAN_VALUE);
		} else {
			int N = -1;
			std::stringstream ss;
			ss << K;
			ss >> N;
			if(sample_reader->setKSelectMethod(KSelectMethod::N_PER_CENT, N)) {
				std::cerr << "Invalid 'K' parameter value: " << N << "(must be 'A', 'M' or between 0 and 99)." << std::endl;
				return 0;
			}
		}
	}

	// main program
	std::cout << "MAIN PROGRAM" << std::endl;

	std::set<shared_ptr<std::string> > k_mers;
	sample_reader->parse(k_mers);
	for(std::set<shared_ptr<std::string> >::const_iterator it = k_mers.begin(); it != k_mers.end(); ++it)
		std::cout << **it << std::endl;

	return 0;
}
