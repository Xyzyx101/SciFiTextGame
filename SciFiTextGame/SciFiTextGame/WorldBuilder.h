#pragma once
#include<string>

class GrammarTree;
class World;

class WorldBuilder {
public:
	WorldBuilder();
	~WorldBuilder();
	void InitWithFile(std::string filename);
	void BuildWorld(World& world) const;
private:
	GrammarTree* grammarTree;
};

