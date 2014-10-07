#include "World.h"
#include"TokenPool.h"
#include"GameObject.h"
#include"Player.h"

World World::instance;

World::World() {}

World::~World() {}

World& World::Instance() {
	return instance;
}

void World::AddObject( GameObject_ptr object ) {
	if( object->GetType() == GameObject_t::PLAYER ) {
		player = std::dynamic_pointer_cast<Player>(object);
	}
	children.push_back( object );
}

void World::AddObject( GameObject_ptr object, GameObject_ptr newParent ) {
	AddObject( object );
	MoveObject( object, newParent );
}

GameObject_ptr World::GetObjectFromName( std::string name ) const {
	return allObjects.find( TOKEN( name ) )->second;
}

GameObject_ptr World::GetObjectFromToken( Token_ptr objectToken ) const {
	return allObjects.find( objectToken )->second;
}

GameObject_ptr World::GetLocalObject( Token_ptr object ) const {

	// TODO
	return nullptr;
}

Player_ptr World::GetPlayer() const {
	return player;
}

void World::MoveObject( GameObject_ptr object, GameObject_ptr newParent ) {
	// Object.parent may be null if the object is at the root
	if( object->GetParent() ) {
		object->GetParent()->RemoveChild( object );
	}
	newParent->AddChild( object );
}

void World::AddObjectToMap( GameObject_ptr object ) {
	Token_ptr objectToken = TOKEN( object->GetName() );
	allObjects.insert( std::pair<Token_ptr, GameObject_ptr>( objectToken, object ) );
}
