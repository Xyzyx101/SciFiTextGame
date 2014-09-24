#include"GrammarTree.h"
#include"TokenPool.h"

int main() {
	GrammarTree gt;
	
	Token* newToken = new Token( Token::VERB, "bacon");
	gt.AddNode( newToken, "bacon" );
	newToken = new Token( Token::VERB, "cheese" );
	gt.AddNode( newToken, "cheese" );
	newToken = new Token( Token::VERB, "bar" );
	gt.AddNode( newToken, "bar" );
	newToken = new Token( Token::VERB, "ball" );
	gt.AddNode( newToken, "ball" );
	newToken = new Token( Token::VERB, "barry" );
	gt.AddNode( newToken, "barry" );
	newToken = new Token( Token::VERB, "beer" );
	gt.AddNode( newToken, "beer" );
	const Token* const tkTest = TokenPool::Instance( ).NewToken(Token::VERB, "foo");
	return 0;
}