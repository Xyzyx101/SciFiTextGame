#pragma once
#include<string>
#include"CommonTypes.h"
#include"GrammarTree_Node.h"
#include"GrammarTree_Edge.h"

class GrammarTree {
public:
	GrammarTree();
	~GrammarTree();
	Token_ptr const Search( const std::string& string ) const;
	void AddNode(Token_ptr const token, const std::string& alias);
private:
	void AddNode(Node_ptr node, Token_ptr const token, const std::string& alias);
	void Reset();

	Node_ptr		root;
	Node_ptr		current;
	Node_ptr		currentParent;
};
