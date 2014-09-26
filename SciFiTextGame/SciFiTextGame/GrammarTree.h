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
	
	/* This takes an stream buffer and converts it a list of vector. */
	std::vector<Token_ptr> Tokenize(std::istream& inStream) const;
	
private:
	/* This recursively walks the tree and adds the node at the correct place. */
	void AddNode_r(Node_ptr node, Token_ptr const token, const std::string& alias);
	
	/* This will split off the beginning of the stream and return it as a token.
		The stream will be updated with each call. */
	Token_ptr Find(Node_ptr node, std::istream& inStream) const;

	void Reset();

	Node_ptr		root;
};
