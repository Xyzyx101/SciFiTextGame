#pragma once
#include<string>
#include<iostream>
#include"CommonTypes.h"
#include"GrammarTree_Node.h"
#include"GrammarTree_Edge.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();

	/* This is used to initially build the grammar tree. */
	void AddNode(Token_ptr const token, const std::string& alias);

	Token_ptr const Search( const std::string& string ) const;
	
	/* This converts a stream to a vector of tokens.  The command string will be destroyed in the process. */
	std::vector<Token_ptr> Tokenize(std::string& command) const;
	
private:
	/* This recursively walks the tree and adds the node at the correct place. */
	void AddNode_r(Node_ptr node, Token_ptr const token, const std::string& alias);
	
	/* This recursively decend into the tree and return a token or nullptr if there is no matching entry. */
	Token_ptr Find_r(Node_ptr node, std::string& command) const;

	void Reset();

	Node_ptr		root;
};
