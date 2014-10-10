#pragma once
#include"CommonTypes.h"
#include<vector>
#include<stack>

/* This is a temporary tree structure of game objects used by the WorldBuilder as an
intermediary step between tokens and concrete objects.  Each edge off of the root
points to a node representing an object and each edge off of object nodes points
to that objects properties. */
class SyntaxTree {
public:
	SyntaxTree();
	~SyntaxTree();

	/* Moves up one level in the tree. */
	void								MoveToParent();

	/* Insert node at the current position and keeps the same position. */
	void								InsertChild( Edge_ptr );

	/* Inserts a node at the current position and makes the new node the current position*/
	void								InsertChildAndMakeCurrent( Edge_ptr );

	/* Get a copy of the current nodes children so that the world build can iterate through them*/
	std::vector<Edge_ptr>				GetChildren() const;

	/* Makes the root of the tree the current position. */
	void								Reset();
private:
	Node_ptr							root;
	Node_ptr							currentNode;
	std::stack<Node_ptr>				parentStack;
};
