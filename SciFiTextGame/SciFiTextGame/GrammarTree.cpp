#include "GrammarTree.h"
#include<vector>

GrammarTree::GrammarTree() :
current(nullptr),
currentParent(nullptr) {
	root = new Node();
}

GrammarTree::~GrammarTree() {}

void GrammarTree::Reset() {
	current = root;
	currentParent = nullptr;
}

void GrammarTree::AddNode(Token* token, std::string alias) {
	AddNode(root, token, alias);
}

void GrammarTree::AddNode(Node* node, Token* token, std::string alias) {

	std::vector<Edge>::iterator edgeIter = node->children.begin();

	std::string partial = "";
	while( partial == "" && edgeIter != node->children.end() ) {
		std::string edgeString = edgeIter->prefix;
		for( size_t i = 0; i < edgeString.length(); ++i ) {
			if( alias[i] == edgeString[i] ) {
				partial += alias[i];
			}
		}

		//TODO recursive depth call goes here

		++edgeIter;
	}
	Node* newNode = new Node(token);
	if( partial == "" ) {
		node->children.push_back(Edge(partial, newNode));
	} else {
		std::vector<Edge>::iterator oldEdgeIt = node->children.begin();
		std::string oldString = oldEdgeIt->prefix;
		Node* oldNode = oldEdgeIt->node;
		Node* splitNode = new Node();
		splitNode->children.push_back(Edge(alias.substr(partial.length()), newNode));
		splitNode->children.push_back(Edge(alias.substr(partial.length()), oldNode));
		node->children.push_back(Edge(partial, splitNode));
		node->children.erase(oldEdgeIt);
	}
}

const Token * const GrammarTree::Search(const std::string& string) const {
	return nullptr;
}