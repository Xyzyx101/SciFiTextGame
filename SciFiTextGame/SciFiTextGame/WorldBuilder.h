#pragma once
#include"CommonTypes.h"
#include<string>
#include<memory>
#include<list>
#include<fstream>

class Token;
class GrammarTree;
class SyntaxTree;
class World;

class WorldBuilder {
public:
	WorldBuilder();
	~WorldBuilder();

	/* Imports a dict file and makes a grammar tree used for parsing the data files */
	void							InitGrammarWithFile( const std::string& dictFilename );

	/* Creates the game word from a data file */
	void							Build( const std::string& dataFileName, World& world );

private:
	/* Convert a file stream into a list of tokens */
	std::list<Token_ptr>			TokenizeFile(const std::string& dataFile );

	/* Converts the list of tokens into a syntax tree */
	std::shared_ptr<SyntaxTree>		BuildSyntaxTree( std::list<Token_ptr>& tokenList );

	/* Actually builds the game world */
	void							BuildWorldTree( World& world, std::shared_ptr<SyntaxTree> syntaxTree );

	std::shared_ptr<GrammarTree>	grammarTree;
	std::list<Token_ptr>			tokenList;
	std::shared_ptr<SyntaxTree>		syntaxTree;
};
