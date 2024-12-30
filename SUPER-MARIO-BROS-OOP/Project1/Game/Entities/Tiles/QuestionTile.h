#pragma 
#include "MoveUpTile.h"
#include "../../../Utils/EntityManager.h"
#include "../EntityFactory.h"
#include "../../GameConfig.h"
#include <vector>

class QuestionTile : public MoveUpTile {
	bool isEmpty = false;
	std::vector <std::string> animation;
	int aniloop = 0;
	int frame = 0;
	std::string prop;

public:
	QuestionTile(sf::Vector2f _pos, sf::Vector2f _size, std::string power);

	void update(float deltatime) override;
	void touched(float deltatime) override;
};

