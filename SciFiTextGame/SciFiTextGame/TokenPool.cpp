#include"TokenPool.h"
#include"Token.h"
#include<memory>
#include<fstream>
#include<assert.h>

TokenPool TokenPool::instance;

TokenPool::TokenPool() {}

TokenPool::~TokenPool() {}

TokenPool& TokenPool::Instance() {
	return instance;
}

/*TokenPool& TokenPool::operator=(const TokenPool& rhs) {
	return instance;
}*/

Token_ptr TokenPool::NewToken(std::string type, std::string name) {
	Token::TokenType tokenType;
	if( type == "VERB" ) {
		tokenType = Token::TokenType::VERB;
	} else if( type == "NOUN" ) {
		tokenType = Token::TokenType::NOUN;
	} else if( type == "LIST_SEPERATOR" ) {
		tokenType = Token::TokenType::LIST_SEPERATOR;
	} else if( type == "PUNC" ) {
		tokenType = Token::TokenType::PUNC;
	} else if( type == "DATA_TYPE" ) {
		tokenType = Token::TokenType::DATA_TYPE;
	} else if( type == "STRING" ) {
		return nullptr;
	}
	std::map<std::string, Token_ptr>::iterator checkToken = tokenMap.find( name );
	if(  checkToken != tokenMap.end() ) {
		return checkToken->second;
	}
	Token_ptr newToken = std::make_shared<Token>( tokenType, name );
	tokenMap.insert( std::pair<std::string, Token_ptr>( name, newToken ) );
	return newToken;
}

Token_ptr const TokenPool::GetToken(const std::string& name) const {
	auto it = tokenMap.find(name);
	if( it == tokenMap.end() ) {
		return nullptr;
	} else {
		return it->second;
	}
}

