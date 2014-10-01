#include "World.h"

World World::instance;

World::World() {}


World::~World() {}

World& World::Instance() {
	return instance;
}