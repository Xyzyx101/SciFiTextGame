#include "World.h"

World World::instance;

World::World() {}

World::~World() {}

World& World::Instance() {
	return instance;
}

void World::AddObject( GameObject_ptr object ) {
	children.push_back( object );
}