#pragma once
#include<string>
#include<map>
#include"CommonTypes.h"

class TokenPool {
public:
	/* Used to get access to the one instance of the token pool */
	static TokenPool&					Instance();

	/* New token takes in the type as a string but converts it to an enum in the actual token */
	Token_ptr							NewToken( std::string type, std::string name );

	Token_ptr const						GetToken( const std::string& name ) const;

private:
	TokenPool();
	~TokenPool();
	TokenPool( const TokenPool& src ) = delete;
	TokenPool& operator=(const TokenPool& rhs) = delete;
	
	std::map<std::string, Token_ptr>	tokenMap;
	static TokenPool					instance;
};

/* This is just sugar to keep the game code cleaner */
inline Token_ptr TOKEN( const std::string& name ) {
	return TokenPool::Instance().GetToken( name );
}
