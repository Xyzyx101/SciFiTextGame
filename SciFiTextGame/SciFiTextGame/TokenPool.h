#pragma once
#include<string>
#include<map>
#include"CommonTypes.h"

/* Tokens represent all of the verbs and nouns known to the grammar tree.  Tokens are
never created or destroyed by game code.  They are created when the world is built and
used by game code using the TOKEN("name") function. */
class TokenPool {
public:
	/* Used to get access to the one instance of the token pool */
	static TokenPool&								Instance();

	/* New token takes in the type as a string but converts it to an enum in the actual token */
	Token_ptr										NewToken( std::string type, std::string name );

	/* Returns a token or a nullptr if no token exists */
	Token_ptr const									GetToken( const std::string& name );

private:
	/* There is one instance of token pool and it cannot be created, changed, destroyed or
	to a function in game code. */
	TokenPool();
	~TokenPool();
	TokenPool( const TokenPool& src ) = delete;
	TokenPool& operator=(const TokenPool& rhs) = delete;

	/* Tokens are not case sensative and will always be stored in all caps. */
	void											AllCaps( std::string& aString );

	std::map<std::string, Token_ptr>				tokenMap;
	static TokenPool								instance;
};

/* This is just sugar to keep the game code cleaner */
inline Token_ptr TOKEN( const std::string& name ) {
	return TokenPool::Instance().GetToken( name );
}
