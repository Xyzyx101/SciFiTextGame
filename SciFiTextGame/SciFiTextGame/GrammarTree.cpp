#include "GrammarTree.h"
#include<vector>

GrammarTree::GrammarTree() :
current(nullptr),
currentParent(nullptr) {
	root = std::make_shared<Node>();
}

GrammarTree::~GrammarTree() {}

void GrammarTree::Reset() {
	current = root;
	currentParent = nullptr;
}

void GrammarTree::AddNode(Token_ptr const token, const std::string& alias) {
	AddNode(root, token, alias);
}

void GrammarTree::AddNode(Node_ptr node, Token_ptr const token, const std::string& alias) {

	std::vector<Edge_ptr>::iterator edgeIter = node->children.begin();

	std::string partial = "";
	while( edgeIter != node->children.end() ) {
		std::string edgeString = (*edgeIter)->prefix;
		for( size_t i = 0; i < edgeString.length(); ++i ) {
			if( alias[i] == edgeString[i] ) {
				partial += alias[i];
			} else {
				break;
			}
		}
		if( partial == edgeString ) {
			AddNode((*edgeIter)->node, token, alias.substr(partial.length()));
			return;
		} else if( partial != "" ) {
			break;
		}
		++edgeIter;
	}
	Node_ptr newNode = std::make_shared<Node>(token);
	if( partial == "" ) {
		node->children.push_back(std::make_shared<Edge>(alias, newNode));
	} else {
		std::string oldString = (*edgeIter)->prefix;
		Node_ptr oldNode = (*edgeIter)->node;
		node->children.erase(edgeIter);
		Node_ptr splitNode = std::make_shared<Node>();
		splitNode->children.push_back(std::make_shared<Edge>(alias.substr(partial.length()), newNode));
		splitNode->children.push_back(std::make_shared<Edge>(oldString.substr(partial.length()), oldNode));
		node->children.push_back(std::make_shared<Edge>(partial, splitNode));
	}
}

Token_ptr const GrammarTree::Search(const std::string& string) const {

	//FIXME - this should do stuff
	return nullptr;

}