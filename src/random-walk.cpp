#include "random-walk.h"
#include <sstream>
#include <ios>
#include <iomanip>
#include "unistd.h"

/**
 * A struct that holds that arguments that the program is being run with.
 */
struct arguments {
	///Filename of the graph file (containing nodes and edges)
    std::string filename = "data/nodes.txt";
#ifdef GRAPHICS
	///Path to where the data from computation has been stored
	std::string storedDataPath = "data/save.txt";
	///Beginning of the path to which images should be written
    std::string dataPath = "data/img/a";
#else
	///Path to file containing only the data to restart from
	std::string storedDataPath = "data/saveLAST.txt";
	///Path to where data should be stored
    std::string dataPath = "data/save.txt";
#endif
	///Number of steps to take/read
    int nCount = 50;
	///How often (in steps) to output data
    int writeInterval = 1;
	///Size of a single timestep
    double dt = 0.1;
	///True if no generation should be perform (e.g. only print help)
	bool quitAfterArgs = false;
	///True when computation should be resumed from some point
	bool restart = false;
	///True if we are allowed to over-write data
	bool force = false;
    ///Number of threads to use
    unsigned int threads = 1;
};

/**
 * Read command line arguments and return correct settings.
 *
 * @param argc The number of elements in argv
 * @param argv Each argument
 * @return A struct arguments with parameters following the arguments in argv.
 */
arguments parse_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    std::shared_ptr<LinearAntElement> e(new LinearAntElement());
    algorithmCreator create = CurrentWalk::create;
	arguments args = parse_args(argc, argv);
	if (args.quitAfterArgs) {
		return 0;
	}
    
#ifdef GRAPHICS
    generateGraphics(args.filename, args.storedDataPath, args.dataPath, e, create, args.nCount, args.writeInterval, args.force);
#else
    omp_set_num_threads(args.threads);
	if (args.restart) {
		generateData(args.filename, args.dataPath, e, create, args.nCount, args.dt, args.writeInterval, args.force, args.storedDataPath);
	} else {
		generateData(args.filename, args.dataPath, e, create, args.nCount, args.dt, args.writeInterval, args.force);
	}
#endif
    return 0;
}

arguments parse_args(int argc, char* argv[]) {
	arguments args;
	int c;
	while ((c = getopt(argc, argv, "i:d:o:n:w:t:p:fh")) != -1) {
		switch (c) {
			case 'i':
				args.filename = optarg;
				break;
			case 'd':
				args.storedDataPath = optarg;
				args.restart = true;
				break;
			case 'o':
				args.dataPath = optarg;
				break;
			case 'n':
				args.nCount = std::atoi(optarg);
				break;
			case 'w':
				args.writeInterval = std::atoi(optarg);
				break;
			case 't':
				args.dt = std::atof(optarg);
				break;
			case 'f':
				args.force = true;
				break;
            case 'p':
                args.threads = std::atoi(optarg);
                break;
			case 'h':
				std::cout << "usage: " << argv[0] << " <options>\n\n";
				std::cout << "Options: \n";
				std::cout << "  -i\tThe input to read data from, which is a file defining a set of nodes and their connections.\n";
				std::cout << "  -d\tThe Already stored data, if any exists. This is used when generating graphics or continuing calculations from a stored data point.\n";
				std::cout << "  -o\tThe output to write to. If generating data, this is a text file. If generating graphics, this is the beginning of the path to the images, e.g. 'img/run1_' if images should be saved in files having the format 'img/run1_000001.png'.\n";
				std::cout << "  -n\tThe number of time steps to take, or if generating graphics, the number of images to generate.\n";
				std::cout << "  -w\tWith what interval to write to file, e.g. 5 if data should be stored every fifth iteration. When generating graphics, 5 would be interpreted as writing an image to file for every fifth piece of data stored in the input file.\n";
				std::cout << "  -t\tThe time step to use, only relevant when generating data.\n";
                std::cout << "  -p\tThe number of threads to use.\n";

				std::cout << "\n";
				args.quitAfterArgs = true;
				break;
			default:
				std::cout << "Found unexpected argument " << c << "\n";
		}
	}
	return args;
}
