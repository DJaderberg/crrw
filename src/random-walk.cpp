#include "random-walk.h"

int main() {
	std::cout << "Hello World!\n";
	std::shared_ptr<AntElement> e(new AntElement());
	std::string filename = "test/nodes.txt";
	PositionedNodeSet set = PositionedNodeSet(filename, e);
	std::cout << set.toString();
	
    NodeSetGraphics graphics = NodeSetGraphics();
    
    for (int i = 0; i < 100000; ++i) {
		set.takeStep(0.1);
	}
    
    graphics.writeToFile(set, "images/image.png");
    
    return 0;
}
