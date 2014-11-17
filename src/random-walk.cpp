#include "random-walk.h"
#include <sstream>
#include <ios>
#include <iomanip>

struct arguments {
    std::string filename = "data/nodes.txt";
    std::string dataPath = "data/save.txt";
    int nCount = 5;
    int writeDataInterval = 1;
    int writeGraphicsInterval = 1;
    std::string imageSavePath = "img/a";
    double dt = 0.1;
};

arguments parse_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    std::shared_ptr<AntElement> e(new AntElement());
    algorithmCreator create = CurrentWalk::create;
	arguments args = parse_args(argc, argv);
    
#ifdef GRAPHICS
    generateGraphics(args.filename, args.dataPath, args.imageSavePath, e, create, args.nCount/args.writeDataInterval, args.writeGraphicsInterval);
#else
    generateData(args.filename, args.dataPath, e, create, args.nCount, args.dt, args.writeDataInterval);
    //generateData(filename, dataPath, e, create, nCount, dt, writeDataInterval, "data/saveLAST.txt");
#endif
    return 0;
}

arguments parse_args(int argc, char* argv[]) {
	arguments args;
	return args;
}
