#include "TokenPool.h"

TokenPool TokenPool::instance;

TokenPool::TokenPool() {}

TokenPool::~TokenPool() {}

TokenPool& TokenPool::Instance() {
	return instance;
}

TokenPool& TokenPool::operator=(const TokenPool& rhs) {
	return instance;
}

const Token* const TokenPool::NewToken( Token::TokenType type, std::string name ) {

	//TODO
	return new Token(Token::VERB, "FIXME" );
}

const Token* const TokenPoolGetToken( std::string name ) {

	//TODO
	return new Token( Token::VERB, "FIXME" );
}
