#include "random-walk.h"
#include <sstream>
#include <ios>
#include <iomanip>

int main() {
    std::string filename = "data/nodes2d.txt";
    std::string dataPath = "data/save.txt";
    std::shared_ptr<AntElement> e(new AntElement());
    algorithmCreator create = CurrentWalk::create;
    int nCount = 1000;
    int writeInterval = 5;
    
#ifdef GRAPHICS
    std::string imageSavePath = "img/a";
    generateGraphics(filename, dataPath, imageSavePath, e, create, nCount, writeInterval);
#else
    double dt = 0.1;
    generateData(filename, dataPath, e, create, nCount, dt, writeInterval);
#endif
    return 0;
}

