#include "Cable.h"
#include"World.h"
#include"TokenPool.h"
#include<string>

Cable::Cable( std::string name, std::string description, std::string longDescription, std::string detail )
: GameObject( name, description, longDescription, detail ),
oneEnd( nullptr ),
theOtherEnd( nullptr ) {}

Cable::~Cable() {}

const std::string Cable::GetLongDescription() const {
	std::string fullDesc = longDescription;
	if( oneEnd != nullptr &&
		World::Instance().IsObjectLocal( TOKEN( oneEnd->GetName() ) ) ) {
		fullDesc += "  One end of the " + description + " is attached to the " + oneEnd->GetDescription() + ".";
	}
	if( theOtherEnd != nullptr &&
		World::Instance().IsObjectLocal( TOKEN( theOtherEnd->GetName() ) ) ) {
		fullDesc += "  One end of the " + description + " is attached to the " + theOtherEnd->GetDescription() + ".";
	}
	return fullDesc;
}

const std::string Cable::GetDetail() const {
	if( detail == "" ) {
		return GetLongDescription();
	} else {
		std::string fullDetail = detail;
		if( oneEnd != nullptr ) {
			fullDetail += "  One end of the " + description + " is attached to the " + oneEnd->GetDescription() + ".";
		}
		if( theOtherEnd != nullptr ) {
			fullDetail += "  One end of the " + description + " is attached to the " + theOtherEnd->GetDescription() + ".";
		}
		return fullDetail;
	}
}

void Cable::SetOneEnd( GameObject_ptr object ) {
	oneEnd = object;
}

void Cable::SetTheOtherEnd( GameObject_ptr object ) {
	theOtherEnd = object;
}

bool Cable::OneEndPlugged() {
	if( oneEnd == nullptr ) {
		return false;
	} else {
		return true;
	}
}

bool Cable::BothEndsPlugged() {
	if( oneEnd == nullptr || theOtherEnd == nullptr ) {
		return false;
	} else {
		return true;
	}
}