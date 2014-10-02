#include "WorldBuilder.h"
#include"GrammarTree.h"
#include<fstream>
#include<memory>
#include<string>

WorldBuilder::WorldBuilder() : 
grammarTree( std::make_shared<GrammarTree>( ) ) {}

WorldBuilder::~WorldBuilder() {
}

void WorldBuilder::InitGrammarWithFile(const std::string& dictFileName) {
	grammarTree->AddDictionary("importer.dict");		
}

void WorldBuilder::Build( const std::string& dataFile, World& world ) {
	tokenList = TokenizeFile(dataFile);
	syntaxTree = BuildSyntaxTree(tokenList);
	BuildWorldTree(world, syntaxTree);
}

std::list<Token_ptr> WorldBuilder::TokenizeFile( const std::string& dataFile ) {
	std::ifstream file;
	std::string data;
	std::list<Token_ptr> tokenList;
	file.open(dataFile, std::fstream::in);
	if( file.good() ) {
		file >> data;
		tokenList = grammarTree->Tokenize(data);
	} else {
		std::cout << std::endl << "Error opening file <" << dataFile << ">" << std::endl;
	}
	return tokenList;
}

std::shared_ptr<SyntaxTree>	WorldBuilder::BuildSyntaxTree( std::list<Token_ptr>& tokenList ) {
	
}

void WorldBuilder::BuildWorldTree( World& world, std::shared_ptr<SyntaxTree> syntaxTree ) {

}