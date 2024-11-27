#pragma once
#include "Tile.h"
#include "../../GameConfig.h"

class PipeHead : public Tile {
private:
	bool isTele = false;
	bool isUp = false;
	int x = 0;
	int y = 0;
	float cameraBase = 0;

public:
	PipeHead(sf::Vector2f pos, sf::Vector2f size, bool isTrans, std::string properties, std::string type);
	ENTITY_TYPE getType() override;
	void affectOther(Entity* other) override;
};

