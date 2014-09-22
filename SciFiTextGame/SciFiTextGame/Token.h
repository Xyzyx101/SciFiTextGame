#pragma once

#include<string>

class Token {

public:

	friend class TokenLibrary;

	enum TokenType {
		VERB,
		NOUN,
		LIST_SEPERATOR,
		COMMAND_SEPERATOR
	};

	~Token();
	TokenType GetType() const;
	const std::string& GetName() const;
private:
	Token(TokenType type, std::string name);
	TokenType type;
	const std::string name;
};

