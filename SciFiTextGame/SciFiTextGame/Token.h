#pragma once

#include<string>

/* Tokens represent all of the Verbs and Nouns entered by the player as well as
the syntax structure used by WorldBuilder to interpret data files.
Tokens are created once from dict files or added by the world builder using the
newToken interface of the Token Pool.  Tokens in game code are always represented as
shared pointers to const Token objects and are never created or destroyed.  */
class Token {
public:
	enum TokenType {
		VERB,
		NOUN,
		LIST_SEPERATOR,
		PUNC,
		DATA_TYPE,
		STRING,
		EXIT,
		FLUFF
	};

	Token( TokenType type, std::string property );
	~Token();
	TokenType					GetType() const;
	const std::string&			GetProperty() const;
private:
	TokenType					type;
	const std::string			property;
};
