#pragma once

#include<string>

class Token {
public:
	enum TokenType {
		VERB,
		NOUN,
		LIST_SEPERATOR,
		PUNC,
		DATA_TYPE,
		STRING,
		EXIT
	};

	Token( TokenType type, std::string property );
	~Token();
	TokenType					GetType() const;
	const std::string&			GetProperty() const;
private:
	TokenType					type;
	const std::string			property;
};
