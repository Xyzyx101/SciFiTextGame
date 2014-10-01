#include"CommonTypes.h"
#include"GrammarTree.h"
#include"TokenPool.h"
#include <iostream>

int main() {
	TokenPool::Instance().NewToken("VERB", "bacon");
	TokenPool::Instance().NewToken("VERB", "cheese");
	TokenPool::Instance().NewToken("VERB", "bar");
	TokenPool::Instance().NewToken("VERB", "ball");
	TokenPool::Instance().NewToken("VERB", "barry");
	TokenPool::Instance().NewToken("VERB", "beer");

	GrammarTree gt;
	gt.AddNode(TOKEN("bacon"), "bacon");
	gt.AddNode(TOKEN("cheese"), "cheese");
	gt.AddNode(TOKEN("bar"), "bar");
	gt.AddNode(TOKEN("ball"), "ball");
	gt.AddNode(TOKEN("barry"), "barry");
	gt.AddNode(TOKEN("beer"), "beer");
	gt.AddNode(TOKEN("checkers"), "checkers");

	do {
		std::cout << "Type stream to tokenize : ";
		std::string command;
		std::getline(std::cin, command);

		std::vector<Token_ptr> test = gt.Tokenize(command);
	} while( true );

	system("pause");

	return 0;
}
