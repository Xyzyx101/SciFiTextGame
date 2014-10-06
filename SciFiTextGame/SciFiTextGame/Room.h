#pragma once
#include"GameObject.h"
#include"CommonTypes.h"
#include<map>

class Room : public GameObject {
public:
	Room(std::string name, std::string description, std::string longDescription);
	virtual ~Room();
	GameObject_ptr							GetExit(Token_ptr alias) const;
	void									AddExit(Token_ptr alias, Room_ptr newExit);

	static inline GameObject_t				GetType() { return ROOM; };

private:
	std::map<Token_ptr, GameObject_ptr>		exits;
};

