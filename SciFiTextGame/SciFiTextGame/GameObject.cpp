#include"GameObject.h"
#include"World.h"

GameObject::GameObject( std::string name, std::string description, std::string longDescription ) :
name( name ),
description( description ),
longDescription( longDescription ),
canBePickedUp(false) {}

GameObject::~GameObject() {}

const std::string& GameObject::GetDescription() const {
	return description;
}

const std::string& GameObject::GetLongDescription() const {
	return longDescription;
}

GameObject_ptr GameObject::GetParent() const {
	return parent;
}

void GameObject::SetParent( GameObject_ptr newParent ) {
	parent = newParent;
}

void GameObject::AddChild( GameObject_ptr child ) {
	children.push_back( child );
	/* Get the pointer from world to make sure the pointer is ref counted properly */
	GameObject_ptr sharedThis = World::Instance( ).GetObjectFromName(name);
	child->SetParent( sharedThis );
}

void GameObject::RemoveChild( GameObject_ptr child ) {
	std::vector<GameObject_ptr>::iterator childIter = children.begin();
	while( childIter != children.end() ) {
		if( child == *childIter ) {
			children.erase( childIter );
		}
		++childIter;
	}
}
