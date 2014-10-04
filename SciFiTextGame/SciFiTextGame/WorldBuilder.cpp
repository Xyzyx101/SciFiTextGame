#include "WorldBuilder.h"
#include"GrammarTree.h"
#include"SyntaxTree.h"
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
	std::string fullName = ".\\Data\\";
	fullName += dataFile;
	std::ifstream file;

	std::list<Token_ptr> tokenList;
	file.open(fullName, std::fstream::in);
	if( !file.good() ) {
		std::cout << std::endl << "Error opening file <" << dataFile << ">" << std::endl;
	} else {
		std::string line, fileString;
		while( !file.eof() ) {
			std::getline(file, line);
			fileString += line;
			fileString += " ";
		}

		tokenList = grammarTree->Tokenize(fileString);
	}
	return tokenList;
}

std::shared_ptr<SyntaxTree>	WorldBuilder::BuildSyntaxTree( std::list<Token_ptr>& tokenList ) {
	return std::make_shared<SyntaxTree>();
}

void WorldBuilder::BuildWorldTree( World& world, std::shared_ptr<SyntaxTree> syntaxTree ) {

}