#pragma once
#include<string>
#include<map>
#include"CommonTypes.h"
#include"Token.h"

class TokenPool {
public:
	static TokenPool& Instance();
	void NewToken( Token::TokenType type, std::string name );
	Token_ptr const GetToken(std::string name) const;
private:
	static TokenPool instance;
	TokenPool( );
	~TokenPool( );
	TokenPool(const TokenPool& src) = delete;
	TokenPool& operator=(const TokenPool& rhs);
	std::map<std::string, Token_ptr> tokenMap;
};

