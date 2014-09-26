#include "GrammarTree.h"
#include<vector>

GrammarTree::GrammarTree() {
	root = std::make_shared<Node>();
}

GrammarTree::~GrammarTree() {}

void GrammarTree::AddNode(Token_ptr const token, const std::string& alias) {
	AddNode_r(root, token, alias);
}

void GrammarTree::AddNode_r(Node_ptr node, Token_ptr const token, const std::string& alias) {
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
			AddNode_r((*edgeIter)->node, token, alias.substr(partial.length()));
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

std::vector<Token_ptr> GrammarTree::Tokenize(std::istream& inStream) const {
	std::vector<Token_ptr> tokens;
	while( inStream.good() ) {
		Find(root, inStream);
	}
	return tokens;
}

Token_ptr GrammarTree::Find(Node_ptr node, std::istream& inStream) const {
	int foundElements;
	std::vector<Edge_ptr>::iterator edgeIter = node->children.begin();
	do {
		std::string prefix = (*edgeIter)->prefix;
		while( inStream.good() &&
			   foundElements < prefix.length() ) {
			char element = inStream.get();
			if( element == prefix[foundElements] ) {
				++foundElements;
			} else {
				// no token found
			}
		}
		++edgeIter;
	} while( foundElements == 0 &&
			 edgeIter != node->children.end() )
	/*
	// Begin at the root with no elements found
	Node traverseNode : = root;
	int elementsFound : = 0;

	// Traverse until a leaf is found or it is not possible to continue
	while( traverseNode != null && !traverseNode.isLeaf() && elementsFound < x.length ) {
		// Get the next edge to explore based on the elements not yet found in x
		Edge nextEdge : = select edge from traverseNode.edges where edge.label is a prefix of x.suffix(elementsFound)
			// x.suffix(elementsFound) returns the last (x.length - elementsFound) elements of x

			// Was an edge found?
		if( nextEdge != null ) {
			// Set the next node to explore
		traverseNode: = nextEdge.targetNode;

			// Increment elements found based on the label stored at the edge
			elementsFound += nextEdge.label.length;
		} else {
			// Terminate loop
		traverseNode: = null;
		}
	}

	// A match is found if we arrive at a leaf node and have used up exactly x.length elements
	return (traverseNode != null && traverseNode.isLeaf() && elementsFound == x.length);*/

}