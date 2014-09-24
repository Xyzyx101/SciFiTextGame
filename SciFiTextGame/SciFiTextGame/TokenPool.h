#pragma once
#include"Token.h"
class TokenPool {
public:
	static TokenPool& Instance();
	const Token* const NewToken( Token::TokenType type, std::string name );
	const Token* const GetToken(std::string name);
private:
	static TokenPool instance;
	TokenPool( );
	~TokenPool( );
	TokenPool(const TokenPool& src) = delete;
	TokenPool& operator=(const TokenPool& rhs);
};

