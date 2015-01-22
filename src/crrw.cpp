#include "crrw.h"
#include <sstream>
#include <ios>
#include <iomanip>
#include "unistd.h"

/**
 * A struct that holds that arguments that the program is being run with.
 */
struct arguments {
	///Filename of the graph file (containing nodes and edges)
    std::string filename = "example.txt";
#ifdef GRAPHICS
	///Path to where the data from computation has been stored
	std::string storedDataPath = "example.txt";
	///Beginning of the path to which images should be written
    std::string dataPath = "example";
#else
	///Path to file containing only the data to restart from
	std::string storedDataPath = "example_LAST.txt";
	///Path to where data should be stored
    std::string dataPath = "example.txt";
#endif
	///Number of steps to take/read
    long long nCount = 50;
	///How often (in steps) to output data
    long long writeInterval = 1;
	///Size of a single timestep
    double dt = 0.1;
	///True if no generation should be perform (e.g. only print help)
	bool quitAfterArgs = false;
	///True when computation should be resumed from some point
	bool restart = false;
	///True if we are allowed to over-write data
	bool force = false;
	///True if we should only partition data using METIS
	bool metis = false;
	///Path to store METIS file (containing which partition each original node
	///should be placed in).
	std::string metisPath = "example.txt";
	///The number of parts that METIS should divide that graph into.
	long long metisParts = 1;
	///True if we should only reduce the number of nodes
	bool reduce = false;
	///The maximal distance between nodes that should be joined
	double reduceDist = 0.0;
    ///The file path to the element configuration file
    std::string elementPath = "example.txt";
    ///Number of threads to use
    unsigned int threads = 1;
    /// Boolean for setting if the shortest path should be drawn when generating images
    bool shortestPaths = false;
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
	arguments args = parse_args(argc, argv);
	if (args.quitAfterArgs) {
		return 0;
	}
    std::ifstream elementConfigureStream(args.elementPath);
    std::string line;
    std::getline(elementConfigureStream, line);
    std::shared_ptr<Element> e(new Element(0.0001, 0.001, 1.0, 0.05));
    e->readData(line);
    elementConfigureStream.close();
    algorithmCreator create = CurrentWalk::create;
    
#ifdef GRAPHICS
	if (args.reduce) {
		std::shared_ptr<PositionedNodeSet> set_ptr(new PositionedNodeSet(args.filename, create, e));
		auto newSet = reduceNodes(set_ptr, args.reduceDist);
		newSet->writeTGF(args.dataPath);
		return 0;
	}
	if (args.metis) {
		generateMetis(args.filename, args.dataPath, args.metisPath, e, create, args.metisParts, args.force);
		return 0;
	}
    generateGraphics(args.filename, args.storedDataPath, args.dataPath, e, create, args.nCount, args.writeInterval, args.shortestPaths, args.force);
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
	long long c;
	while ((c = getopt(argc, argv, "i:d:o:n:w:t:fm:q:r:e:p:sh")) != -1) {
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
				args.nCount = (long long) std::atoi(optarg);
				break;
			case 'w':
				args.writeInterval = (long long) std::atoi(optarg);
				break;
			case 't':
				args.dt = std::atof(optarg);
				break;
			case 'f':
				args.force = true;
				break;
			case 'm':
				args.metis = true;
				args.metisPath = optarg;
				break;
			case 'q':
				args.metisParts = (long long) std::atoi(optarg);
				break;
			case 'r':
				args.reduce = true;
				args.reduceDist = std::atof(optarg);
				break;
			case 'e':
				args.elementPath = optarg;
				break;
            case 'p':
                args.threads = std::atoi(optarg);
                break;
            case 's':
                args.shortestPaths = true;
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
                std::cout << "  -e\tThe file path to the elemet configuration file.\n";
                std::cout << "  -m\tFile path to temporary file used for creating partitioned METIS graphs.\n";
                std::cout << "  -s\tFlag for setting if the shortest paths should be drawn when generating images.\n";

				std::cout << "\n";
				args.quitAfterArgs = true;
				break;
			default:
				std::cout << "Found unexpected argument " << c << "\n";
		}
	}
	return args;
}
