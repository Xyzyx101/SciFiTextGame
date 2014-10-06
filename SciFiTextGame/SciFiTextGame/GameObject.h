#pragma once
#include<string>
#include<vector>
#include<memory>
#include"CommonTypes.h"

enum GameObject_t {
	OBJECT,
	PLAYER,
	ROOM
};

class GameObject {
public:
	/* Adding an object with a null parent will use the world as the parent. */
	GameObject(std::string name, std::string description, std::string longDescription);
	virtual ~GameObject();
	const std::string&				GetName() const;
	const std::string&				GetDescription() const;
	const std::string&				GetLongDescription() const;
	GameObject_ptr					GetParent() const;

	static inline GameObject_t		GetType() { return OBJECT; };

private:
	std::string						name;
	std::string						description;
	std::string						longDescription;
	GameObject_ptr					parent;
	std::vector<GameObject_ptr>		children;
};
