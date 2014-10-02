#pragma once
#include<string>
#include<iostream>
#include<list>
#include"CommonTypes.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();

	/* This is used to initially build the grammar tree. */
	void						AddNode(Token_ptr const token, const std::string& alias);
		
	/* This converts a string to a vector of tokens.  The command string will be destroyed in the process. */
	std::list<Token_ptr>		Tokenize(std::string& command) const;

	/* This uses a custom file format with each line being in the format 'ALIAS TYPE TOKEN' on each line
	The function parses the lines and adds a Token to the token pool and a node*/
	void						AddDictionary( const std::string& dictFile );

private:
	/* This recursively walks the tree and adds the node at the correct place. */
	void						AddNode_r(Node_ptr node, Token_ptr const token, const std::string& alias);
	
	/* This recursively decend into the tree and return a token or nullptr if there is no matching entry. */
	Token_ptr					Find_r(Node_ptr node, std::string& command) const;

	/* This parses one line, adds the token to the token pool and adds the node to grammar tree. */
	void						AddNodeWithString( const std::string& line );

	Node_ptr					root;
};
