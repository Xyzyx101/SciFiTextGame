#pragma once
#include<string>
#include<map>
#include"CommonTypes.h"
#include"Token.h"

class TokenPool {
public:
	static TokenPool& Instance();
	void NewToken( Token::TokenType type, std::string name );
	Token_ptr const GetToken(const std::string& name) const;
private:
	static TokenPool instance;
	TokenPool( );
	~TokenPool( );
	TokenPool(const TokenPool& src) = delete;
	TokenPool& operator=(const TokenPool& rhs);
	std::map<std::string, Token_ptr> tokenMap;
};

inline Token_ptr TOKEN(const std::string& name) {
	return TokenPool::Instance().GetToken(name);
}
