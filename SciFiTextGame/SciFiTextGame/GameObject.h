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
	GameObject( std::string name, std::string description, std::string longDescription );
	virtual ~GameObject();
	inline const std::string&		GetName() const { return name; };
	const std::string&				GetDescription() const;
	const std::string&				GetLongDescription() const;
	GameObject_ptr					GetParent() const;
	void							SetParent( GameObject_ptr newParent );
	void							AddChild( GameObject_ptr child );
	void							RemoveChild( GameObject_ptr child );
	std::vector<GameObject_ptr>&	GetChildren();
	virtual inline GameObject_t		GetType() { return OBJECT; };
	void							SetCanBePickedUp( bool value ) { canBePickedUp = value; };
	virtual inline bool				CanBePickedUp() { return canBePickedUp; };
private:
	std::string						name;
	std::string						description;
	std::string						longDescription;
	GameObject_ptr					parent;
	std::vector<GameObject_ptr>		children;
	bool							canBePickedUp;
};
