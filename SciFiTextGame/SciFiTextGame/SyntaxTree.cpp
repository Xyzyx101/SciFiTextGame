#include"SyntaxTree.h"
#include"CommonTypes.h"
#include"Node.h"
#include"Edge.h"
#include<memory>

SyntaxTree::SyntaxTree() {
	root = std::make_shared<Node>();
	currentNode = root;
}

SyntaxTree::~SyntaxTree() {}

void SyntaxTree::Reset() {
	currentNode = root;
	while( !parentStack.empty() ) {
		parentStack.pop();
	}
}

void SyntaxTree::MoveToParent() {
	if( currentNode == root ) {
		return;
	}
	currentNode = parentStack.top();
	parentStack.pop();
}

void SyntaxTree::InsertChild( Edge_ptr newEdge ) {
	currentNode->children.push_back( newEdge );
}

void SyntaxTree::InsertChildAndMakeCurrent( Edge_ptr newEdge ) {
	InsertChild(newEdge);
	parentStack.push(currentNode);
	currentNode = newEdge->node;
}


