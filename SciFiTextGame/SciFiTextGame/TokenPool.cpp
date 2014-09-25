#include"TokenPool.h"
#include<memory>

TokenPool TokenPool::instance;

TokenPool::TokenPool() {}

TokenPool::~TokenPool() {}

TokenPool& TokenPool::Instance() {
	return instance;
}

TokenPool& TokenPool::operator=(const TokenPool& rhs) {
	return instance;
}

void TokenPool::NewToken(Token::TokenType type, std::string name) {
	Token_ptr newToken = std::make_shared<Token>(type, name);
	tokenMap.insert(std::pair<std::string, Token_ptr>(name, newToken));
}

Token_ptr const TokenPool::GetToken(const std::string& name) const {
	auto it = tokenMap.find(name);
	if( it == tokenMap.end() ) {
		return nullptr;
	} else {
		return it->second;
	}
}
