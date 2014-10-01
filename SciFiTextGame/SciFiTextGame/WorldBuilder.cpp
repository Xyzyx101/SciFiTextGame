#include "WorldBuilder.h"
#include"GrammarTree.h"
#include<fstream>

WorldBuilder::WorldBuilder() : 
grammarTree(NULL) {}

WorldBuilder::~WorldBuilder() {
	delete grammarTree;
}

void WorldBuilder::InitWithFile(const std::string& filename) {
	grammarTree = new GrammarTree();
	grammarTree->AddDictionary("importer.dict");		
}

void WorldBuilder::BuildWorld( const std::string&, World& world ) const {

}