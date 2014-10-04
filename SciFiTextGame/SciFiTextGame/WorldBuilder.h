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
	void							TokenizeFile(const std::string& dataFile );

	/* Converts the list of tokens into a syntax tree */
	void							BuildSyntaxTree();

	/* Removes the next two token from the token list and adds it to the syntax tree.  Two
	tokens are removed because data is generally stored as type-value pairs. */
	void							AddNextToken( Token_ptr nextToken );

	/* This is used to a list of objects to the root or other list of properties to a 
	property of an object.  Can be called recursively to add lists of lists. */
	void							AddList_r();

	/* Verifies that the next token is the expected token.  Removes the token from the list and
	returns true is it is good and displays an error if it bad. */
	bool							ExpectingToken( Token_ptr expectedToken );

	/* Actually builds the game world */
	void							BuildWorldTree();

	std::shared_ptr<GrammarTree>	grammarTree;
	std::list<Token_ptr>			tokenList;
	std::shared_ptr<SyntaxTree>		syntaxTree;
};
