#include"GameObject.h"

GameObject::GameObject(std::string name, GameObject_ptr parent, std::string description, std::string longDescription) :
name(name),
parent(parent),
description(description),
longDescription(longDescription) {
}

GameObject::~GameObject() {
}

const std::string& GameObject::GetName() const {
	return name;
}

const std::string& GameObject::GetDescription() const {
	return description;
}

const std::string& GameObject::GetLongDescription() const {
	return longDescription;
}

GameObject_ptr GameObject::GetParent() const {
	return parent;
}

