#include<iostream>
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
		(",K", value<std::string>(), "k-mer length selection mode:\n'A' - mean sample length\n'M' - median sample length\n N - take N% of the longest samples")
		(",k", value<int>(), "k-mer length")
		("input-file,i", value<std::string>(), "input file for the program(by default data is read from standard input)")
		("output-file,o", value<std::string>(), "output file for data(must not exist, by default data is written to standard output)")
		(",d", value<std::string>(), "output file for a DOT format file, representing De Bruijn graph")
		(",r", bool_switch(&sample_generator_mode), "sample generator mode")
		(",s", value<std::string>(), "input sequence for sample generator mode")
		(",l", value<int>(), "sample length for sample generator mode")
		(",n", value<int>(), "sample count for sample generator mode")
		(",c", "force sample generator mode to generate samples for a consistent Euler graph")
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

	// open input file for reading
	if(vm.count("input-file")) {
		std::string input_file_name = vm["input-file"].as<std::string>();
	}
	
	std::cout << "Hello World - execution of the main program" << std::endl;

	return 0;
}