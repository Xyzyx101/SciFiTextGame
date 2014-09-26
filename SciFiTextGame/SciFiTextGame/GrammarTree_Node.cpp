#include "GrammarTree_Node.h"

Node::Node() :
token(nullptr) {}

Node::Node(Token_ptr const token) :
token(token) {}

Node::~Node() {
}
