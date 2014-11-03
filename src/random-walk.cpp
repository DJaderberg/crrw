#include "random-walk.h"

int main() {
	std::cout << "Hello World!\n";
	std::shared_ptr<AntElement> e(new AntElement());
	std::shared_ptr<Source> a1(new Source(1,e));
    std::shared_ptr<Node> a2(new Node(e));
    
	std::unordered_map<unsigned int,std::shared_ptr<Node>> bNeighbors;
    std::unordered_map<unsigned int,double> bDistances;
    
    bNeighbors[a1->getId()] = a1;
    bDistances[a1->getId()] = 3;
    
    bNeighbors[a2->getId()] = a2;
    bDistances[a2->getId()] = 5;
    
    std::shared_ptr<Node> b(new Node(bNeighbors, bDistances, e));

    for (int i = 0; i < 3; i++) {
        std::cout << i << "\n";
        std::cout << a1->toString();
        a1->takeStep(1);
        a2->takeStep(1);
        b->takeStep(1);
    }
    return 0;
}
