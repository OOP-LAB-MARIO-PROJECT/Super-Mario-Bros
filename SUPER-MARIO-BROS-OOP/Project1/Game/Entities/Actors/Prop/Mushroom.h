#include "Collectable.h"
class RedMushroom: public Collectable {
	float dist = 0;
public:
	RedMushroom(sf::Vector2f pos, sf::Vector2f size);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	ENTITY_TYPE getType() override;
};

