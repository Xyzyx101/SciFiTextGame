#include "WorldBuilder.h"
#include"GrammarTree.h"
#include<fstream>

WorldBuilder::WorldBuilder() : 
grammarTree(NULL) {}

WorldBuilder::~WorldBuilder() {
	delete grammarTree;
}

void WorldBuilder::InitWithFile(std::string filename) {
	grammarTree = new GrammarTree();
	grammarTree->BuildTreeWithFile("importer.dict");

	std::string fullname = "/data/";
	fullname += filename;

	std::ifstream fStream;
	fStream.open(fullname, std::ifstream::in);
			
}

void WorldBuilder::BuildWorld(World& world) const {

}