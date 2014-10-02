#include "WorldBuilder.h"
#include"GrammarTree.h"
#include<fstream>
#include<memory>

WorldBuilder::WorldBuilder() : 
grammarTree( std::make_shared<GrammarTree>( ) ) {}

WorldBuilder::~WorldBuilder() {
}

void WorldBuilder::InitGrammarWithFile(const std::string& dictFileName) {
	grammarTree->AddDictionary("importer.dict");		
}

void WorldBuilder::Build( const std::string&, World& world ) {
	tokenList = TokenizeFile();
	syntaxTree = BuildSyntaxTree(tokenList);
	BuildWorldTree(world, syntaxTree);
}

std::list<Token_ptr> WorldBuilder::TokenizeFile( std::ifstream& dataFile ) {

}

std::shared_ptr<SyntaxTree>	WorldBuilder::BuildSyntaxTree( std::list<Token_ptr>& tokenList ) {

}

void WorldBuilder::BuildWorldTree( World& world, std::shared_ptr<SyntaxTree> syntaxTree ) {

}