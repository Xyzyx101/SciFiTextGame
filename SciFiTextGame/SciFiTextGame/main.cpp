#include"CommonTypes.h"
#include"GrammarTree.h"
#include"TokenPool.h"

int main() {
	TokenPool::Instance().NewToken(Token::VERB, "bacon");
	TokenPool::Instance().NewToken(Token::VERB, "cheese");
	TokenPool::Instance().NewToken(Token::VERB, "bar");
	TokenPool::Instance().NewToken(Token::VERB, "ball");
	TokenPool::Instance().NewToken(Token::VERB, "barry");
	TokenPool::Instance().NewToken(Token::VERB, "beer");
	
	GrammarTree gt;
	gt.AddNode(TOKEN("bacon"), "bacon");
	gt.AddNode(TOKEN("cheese"), "cheese");
	gt.AddNode(TOKEN("bar"), "bar");
	gt.AddNode(TOKEN("ball"), "ball");
	gt.AddNode(TOKEN("barry"), "barry");
	gt.AddNode(TOKEN("beer"), "beer");
	
	system("pause");

	return 0;
}
