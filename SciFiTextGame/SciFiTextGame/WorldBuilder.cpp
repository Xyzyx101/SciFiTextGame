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

	/*
	std::ios_base::fmtflags ff;
	ff = file.flags();
	ff |= std::cout.skipws;
	file.flags(ff);*/

	char element;
	std::list<Token_ptr> tokenList;
	file.open(fullName, std::fstream::in);
	if( !file.good() ) {
		std::cout << std::endl << "Error opening file <" << dataFile << ">" << std::endl;
	} else {
		file.seekg(0, file.end);
		int fileLength = file.tellg();
		file.seekg(0, file.beg);
		char * buffer = new char[fileLength];
		file.read(buffer, fileLength);
		tokenList = grammarTree->Tokenize(std::string(buffer));
	}
	return tokenList;
}
/*
std::ios_base::fmtflags ff;
ff = std::cout.flags();
ff &= ~std::cout.basefield;   // unset basefield bits
ff |= std::cout.hex;          // set hex
ff |= std::cout.showbase;     // set showbase
std::cout.flags(ff);
std::cout << 100 << '\n';
*/
/*
std::ifstream is ("test.txt", std::ifstream::binary);
if (is) {
// get length of file:
is.seekg (0, is.end);
int length = is.tellg();
is.seekg (0, is.beg);

char * buffer = new char [length];

std::cout << "Reading " << length << " characters... ";
// read data as a block:
is.read (buffer,length);

if (is)
std::cout << "all characters read successfully.";
else
std::cout << "error: only " << is.gcount() << " could be read";
is.close();

// ...buffer contains the entire file...

delete[] buffer;
}
*/

std::shared_ptr<SyntaxTree>	WorldBuilder::BuildSyntaxTree( std::list<Token_ptr>& tokenList ) {
	return std::make_shared<SyntaxTree>();
}

void WorldBuilder::BuildWorldTree( World& world, std::shared_ptr<SyntaxTree> syntaxTree ) {

}