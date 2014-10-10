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
	/* World builder reads in a data file.  Tokenizes the file. Builds an syntax tree
	representing all of the objects in the file and then actually instatntiates
	all of the game objects and the map.  It also adds all of the objects, aliases
	and exit names to the grammar tree to be used by the parser later.  Note that the
	the grammar tree used by worldbuilder and the main world grammar tree are two different
	instances of GrammarTree with different grammar rules.*/
	WorldBuilder();
	~WorldBuilder();

	/* Imports a dict file and makes a grammar tree used for parsing the data files */
	void							InitGrammarWithFile( const std::string& dictFilename );

	/* Creates the game word from a data file */
	void							Build( const std::string& dataFileName, World& world );

private:
	/* Convert a file stream into a list of tokens */
	void							TokenizeFile( const std::string& dataFile );

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

	/*  Reads the token list and creates a syntax tree. */
	void CreateWorldTreeStructure();

	/* Converts the syntax tree into conrete game objects. */
	void AddAllObjectsToWorld();

	/* Instantiates a game object.  Run in a loop from AddAllObjects to world() */
	void AddObjectToWorld( Token_ptr type, const std::string& name, const std::string& description, const std::string& longDescription, const std::string& detail, bool canBePickedUp ) const;

	/* This adds the name of an object to the main grammar tree.  */
	void AddObjectToDictionary( const std::string& type, const std::string& name ) const;

	/* Adds and object to the world grammar tree with an alias. e.g. 'solar panel' and 'panel' refer to
	same object.*/
	void AddObjectToDictionary( const std::string& type, const std::string& name, const std::string& alias ) const;

	/* Add exits to a room using aliases.  This function and UpdateRoomChildren are the main reasons
	the syntax tree are required.  All of the objects that one object refers to need to exist
	before the game start.  The syntax tree is interpreted in two passes.  One to create
	the objects and the second to create the relationships */
	void AddExitsToRoom( GameObject_ptr room, Node_ptr exitsNode ) const;

	/* Similar to AddExitsToRoom except moves objects into place in the world. */
	void UpdateRoomChildren( GameObject_ptr room, Node_ptr exitsNode ) const;

	/* Holds the importer grammar */
	std::shared_ptr<GrammarTree>	grammarTree;

	/* Holds the tokens created from the data file */
	std::list<Token_ptr>			tokenList;

	/* Temporary intermediary between the token list and actual objects */
	std::shared_ptr<SyntaxTree>		syntaxTree;
};
