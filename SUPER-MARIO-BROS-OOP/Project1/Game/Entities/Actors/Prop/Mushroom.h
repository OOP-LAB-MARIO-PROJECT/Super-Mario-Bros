#include "Collectable.h"
class RedMushroom: public Collectable {
public:
	float dist = 0;
	RedMushroom(sf::Vector2f pos, sf::Vector2f size);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	ENTITY_TYPE getType() override;
};

class GreenMushroom : public RedMushroom {
	GreenMushroom(sf::Vector2f pos, sf::Vector2f size);
	ENTITY_TYPE getType() override;
};