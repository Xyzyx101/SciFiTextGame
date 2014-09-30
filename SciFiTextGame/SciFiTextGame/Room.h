#pragma once
#include "GameObject.h"

class Room : public GameObject {
public:
	Room(std::string name, GameObject_ptr parent, std::string description, std::string longDescription);
	virtual ~Room();
	GameObject_ptr GetExit(std::string name) const;
	void AddExit(GameObject_ptr newExit);

	static inline GameObject_t GetType() { return ROOM; };

private:
	std::vector<GameObject_ptr> exits;
};

