#include "random-walk.h"

int main() {
	std::cout << "Hello World!\n";
	std::shared_ptr<AntElement> e(new AntElement());
	std::string filename = "test/nodes.txt";
	NodeSet set = NodeSet(filename, e);
	std::cout << set.toString();
    return 0;
}
