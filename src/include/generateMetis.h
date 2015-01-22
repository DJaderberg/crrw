

#pragma once
#include "positionedNodeSet.h"
#include <string>
#include <fstream>
#include "miscFunctions.h"

void generateMetis(std::string nodePath, std::string dataSavePath, std::string metisPath, std::shared_ptr<Element> e, algorithmCreator create, int numPart, bool force); 
