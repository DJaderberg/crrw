
#ifdef GRAPHICS
#include "generateMetis.h"

void generateMetis(std::string nodePath, std::string dataPath, std::string metisPath, std::shared_ptr<Element> e, algorithmCreator create, int numPart, bool force) {
    if (!force && (exists(dataPath) || exists(metisPath))) {
        std::cout << "ERROR in generateMetis: save file already exists.\n";
        std::cout << "Metis generation aborted.\n";
        return;
    }
	
    PositionedNodeSet set = PositionedNodeSet(nodePath, create, e);
	std::string numPartStr = std::to_string(numPart);
	set.writeMETIS(metisPath);
	system(("gpmetis " + metisPath + " " + numPartStr).c_str());
	set.readMETIS(metisPath + ".part." + numPartStr, dataPath, numPart);
}

#endif

