#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#include<boost/program_options.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graphviz.hpp>
#include<boost/graph/graph_traits.hpp>

#include "Generator.h"
#include "Assembler.h"
#include "KSelector.h"
#include "FixedKSelector.h"
#include "PercentageKSelector.h"
#include "MeanKSelector.h"
#include "Exceptions.h"
using namespace boost::program_options;


int main(int argc, char **argv) {
    try {
	    // define program options
	    options_description desc("Allowed options:");
	    desc.add_options()
		    ("help,h", "display available options")
		    ("k,k", value<int>(), "k-mer length(default is 5)")
		    ("K,K", value<std::string>(), "k-mer length selection mode:\n'A' - mean sample length\n'M' - median sample length\n N - take N% of the longest samples")
		    ("input-file,i", value<std::string>(), "input file for the program(by default data is read from standard input)")
		    ("output-file,o", value<std::string>(), "output file for data(must not exist, by default data is written to standard output)")
		    ("d,d", value<std::string>(), "output file for a DOT format file, representing De Bruijn graph")
		    ("r,r", "sample generator mode")
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

    
        if (vm.count("r")){ //generator mode
            std::cout << "Generator mode" << std::endl;
            dnasm::Generator generator;
            if(vm.count("input-file")){
                generator.readInputSequence(vm["input-file"].as<std::string>());
            }
            if(vm.count("s")){
                generator.setInputSequence(dnasm::Sequence(vm["s"].as<std::string>()));
            }
            if(vm.count("output-file")){
                generator.setOutputFilename(vm["output-file"].as<std::string>());
            }
            if(vm.count("l")){
                generator.setFragmentsLength(vm["l"].as<int>());
            }
            if(vm.count("n")){
                generator.setFragmentsNb(vm["n"].as<int>());
            }
            if(vm.count("c")){
                generator.setCorectness(true);
            }
            generator();
            return 0;

        }else { //assembler mode
            std::cout << "Assembler mode" << std::endl;

            dnasm::Assembler assembler;
            if(vm.count("input-file")){
                assembler.readInputFile(vm["input-file"].as<std::string>());
            } else {
                assembler.readInputStream(std::cin);
            } 
            if (vm.count("output-file")){
                assembler.setOutputFile(vm["output-file"].as<std::string>());   
            }
            if (vm.count("d")){
                assembler.setOutputDotFile(vm["d"].as<std::string>());
            }
            if (vm.count("k")){
                assembler.setKSelector(std::unique_ptr<dnasm::KSelector>(new dnasm::FixedKSelector(vm["k"].as<int>())));
            } else if (vm.count("K")){            
                switch (vm["K"].as<char>()){
                case 'A':
                    assembler.setKSelector(std::unique_ptr<dnasm::KSelector>(new dnasm::MeanKSelector));
                    break;
                case 'N':
                    assembler.setKSelector(std::unique_ptr<dnasm::KSelector>(new dnasm::PercentageKSelector(vm["N"].as<int>())));
                    break;
                default:
                    assembler.setKSelector(std::unique_ptr<dnasm::KSelector>(new dnasm::PercentageKSelector));
                    break;
                }
            } else {
                assembler.setKSelector(std::unique_ptr<dnasm::KSelector>(new dnasm::PercentageKSelector));
            }
            assembler();
            return 0;
        }
    } catch (dnasm::AsmException e) {
        std::cerr << e.getMessage() << std::endl;
    } catch (std::exception e){
        std::cerr << "Exception: " << e.what();
    }
}
