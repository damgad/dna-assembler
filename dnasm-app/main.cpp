#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#include<boost\program_options.hpp>
#include<boost\graph\adjacency_list.hpp>
#include<boost\graph\graphviz.hpp>
#include<boost\graph\graph_traits.hpp>

#include "SampleReader.h"
#include "SharedStringComparator.h"

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

	std::vector<std::string> vertices;
	std::set<std::pair<int, int> > edges;

	sample_reader->parse(vertices, edges);

	typedef boost::adjacency_list<listS, vecS, directedS> Graph;
	Graph de_bruijn_graph(edges.begin(), edges.end(), vertices.size());

	// open file for DOT format graph output
	if(vm.count("d")) {
		std::string dot_file_name = vm["d"].as<std::string>();
		std::ofstream dot_file_stream(dot_file_name, std::ofstream::out | std::ofstream::trunc);
		if(dot_file_stream == 0) {
			std::cerr << "Could not open file \"" << dot_file_name << "\" for writing." << std::endl;
			return 0;
		}
		boost::write_graphviz(dot_file_stream, de_bruijn_graph, make_label_writer(&vertices[0]));
	}

	boost::graph_traits<Graph>::vertex_iterator v, v_end;
	std::tie(v, v_end) = boost::vertices(de_bruijn_graph);
	
	boost::graph_traits<Graph>::out_edge_iterator e, e_end, e_tmp;
	std::tie(e, e_end) = boost::out_edges(*v, de_bruijn_graph);

	std::list<boost::graph_traits<Graph>::vertex_descriptor> sequence_vertices;
	boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
	vertex_descriptor = boost::source(*e, de_bruijn_graph);
	sequence_vertices.push_back(vertex_descriptor);
	
	while(e != e_end) {
		vertex_descriptor = boost::target(*e, de_bruijn_graph);
		sequence_vertices.push_back(vertex_descriptor);

		e_tmp = e;
		std::tie(e, e_end) = boost::out_edges(vertex_descriptor, de_bruijn_graph);
		boost::remove_edge(e_tmp, de_bruijn_graph);	
	}
	
	// main program
	std::cout << "MAIN PROGRAM" << std::endl;
	for(std::list<boost::graph_traits<Graph>::vertex_descriptor>::const_iterator it = sequence_vertices.begin(); it != sequence_vertices.end(); ++it)
		std::cout << vertices[*it] << std::endl;


		std::string dot_file_name("tmp.txt");
		std::ofstream dot_file_stream(dot_file_name, std::ofstream::out | std::ofstream::trunc);
		if(dot_file_stream == 0) {
			std::cerr << "Could not open file \"" << dot_file_name << "\" for writing." << std::endl;
			return 0;
		}
		boost::write_graphviz(dot_file_stream, de_bruijn_graph, make_label_writer(&vertices[0]));

	return 0;
}
