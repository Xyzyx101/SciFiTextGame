#pragma once
#include<string>
#include<vector>
#include<memory>
#include"CommonTypes.h"

enum GameObject_t {
	OBJECT,
	PLAYER,
	ROOM,
	CABLE
};

class GameObject {
public:
	/* Adding an object with a null parent will use the world as the parent. */
	GameObject( std::string name, std::string description, std::string longDescription );
	GameObject( std::string name, std::string description, std::string longDescription, std::string detail );
	virtual ~GameObject();

	/* This is used as a runtime check before casting to inherited types. */
	virtual inline GameObject_t			GetType() { return OBJECT; };

	/* Name is the internal name of the object.  Contains underscores and letters.  Never displayed to players. */
	inline const std::string&			GetName() const { return name; };

	/* Description is the in game name seen by the players. */
	const std::string&					GetDescription() const;

	/* Long description is the text representing that object in full room descriptions. */
	virtual const std::string			GetLongDescription() const;
	void								SetLongDescription( const std::string& );

	/* detail is the text displayed when you examine and object. */
	virtual const std::string			GetDetail() const;
	void								SetDetail( const std::string& );

	/* Parent is the object containing this object in the world tree.  Can be a room for anything
	the player might interact with.  The parent could be the player if the item is in inventory.
	The parent could be nullptr if the object exists but not accessable to the player because
	they need to open a dorr or pull a switch.*/
	GameObject_ptr						GetParent() const;
	void								SetParent( GameObject_ptr newParent );

	void								AddChild( GameObject_ptr child );
	void								RemoveChild( GameObject_ptr child );
	std::vector<GameObject_ptr>&		GetChildren();

	/* canBePickedUp is used as check because not all interactable objects can be carried. */
	void								SetCanBePickedUp( bool value ) { canBePickedUp = value; };
	virtual inline bool					CanBePickedUp() { return canBePickedUp; };
protected:
	std::string							description;
	std::string							longDescription;
	std::string							detail;
private:
	std::string							name;
	GameObject_ptr						parent;
	std::vector<GameObject_ptr>			children;
	bool								canBePickedUp;
};
