#pragma once
#include<string>
#include<iostream>
#include<list>
#include"CommonTypes.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();

	/* This is used to initially build the grammar tree.  Adding the same node more than onece is idempotent. */
	void						AddNode( Token_ptr const token, const std::string& alias );

	/* This converts a string to a vector of tokens.  The command string will be destroyed in the process.
	If the string contains a part that cannot be tokenized an error will be displayed and the list will empty */
	std::list<Token_ptr>		Tokenize( std::string& command ) const;

	/* This uses a custom file format with each line being in the format 'ALIAS TYPE TOKEN' on each line
	The function parses the lines and adds a Token to the token pool and a node*/
	void						AddDictionary( const std::string& dictFile );

private:
	/* This recursively walks the tree and adds the node at the correct place. */
	void						AddNode_r( Node_ptr node, Token_ptr const token, const std::string& alias );

	/* This recursively decend into the tree and return a token or nullptr if there is no matching entry.  If no
	token is found the string that caused it to choke will be in failWord so that an error can be displayed */
	Token_ptr					Find_r( Node_ptr node, std::string& command, std::string& failWord ) const;

	/* This parses a string from the data file and creates a string token. */
	Token_ptr					GetStringToken( std::string& command ) const;

	/* This parses one line, adds the token to the token pool and adds the node to grammar tree. */
	void						AddNodeWithString( const std::string& line );

	void						RemoveLeadingWhitespace( std::string& command ) const;

	Node_ptr					root;
};
