#pragma once
#include<string>
#include<iostream>
#include<vector>
#include"CommonTypes.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();

	/* This is used to initially build the grammar tree. */
	void AddNode(Token_ptr const token, const std::string& alias);

	void AddNodeWithString(std::string line);

	Token_ptr const Search( const std::string& string ) const;
	
	/* This converts a string to a vector of tokens.  The command string will be destroyed in the process. */
	std::vector<Token_ptr> Tokenize(std::string& command) const;

	/* Builds the tree using a datafile*/
	void BuildTreeWithFile(std::string fileName);

private:
	/* This recursively walks the tree and adds the node at the correct place. */
	void AddNode_r(Node_ptr node, Token_ptr const token, const std::string& alias);
	
	/* This recursively decend into the tree and return a token or nullptr if there is no matching entry. */
	Token_ptr Find_r(Node_ptr node, std::string& command) const;

	void Reset();

	Node_ptr		root;
};
