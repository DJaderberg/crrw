#include "random-walk.h"
#include <sstream>
#include <ios>
#include <iomanip>

int main() {
    std::string filename = "data/nodes.txt";
    std::string dataPath = "data/save1d.txt";
    std::shared_ptr<LinearAntElement> e(new LinearAntElement());
    algorithmCreator create = CurrentWalk::create;
    int nCount = 1000;
    int writeInterval = 20;
    
#ifdef GRAPHICS
    std::string imageSavePath = "img/a";
    generateGraphics(filename, dataPath, imageSavePath, e, create, nCount, writeInterval);
#else
    double dt = 0.1;
    generateData(filename, dataPath, e, create, nCount, dt, writeInterval);
#endif
    return 0;
}

