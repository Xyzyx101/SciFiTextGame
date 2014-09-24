#pragma once

#include<string>

class Token {

public:

	enum TokenType {
		VERB,
		NOUN,
		LIST_SEPERATOR,
		COMMAND_SEPERATOR
	};

	Token(TokenType type, std::string name);
	~Token();
	TokenType GetType() const;
	const std::string& GetName() const;
private:
	TokenType type;
	const std::string name;
};
