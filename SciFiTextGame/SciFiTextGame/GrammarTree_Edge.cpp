#include"GrammarTree_Edge.h"

Edge::Edge(std::string prefix, Node_ptr node) :
prefix(prefix),
node(node) {}

Edge::~Edge() {}