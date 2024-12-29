#include "Collectable.h"
#include "../AnimationState/AnimationState.h"


class Star : public Collectable {
	std::shared_ptr<AnimationState> currentState;
	std::map<std::string, std::shared_ptr<AnimationState>> stateCache;
public:
	float dist = 0;
	Star(sf::Vector2f pos, sf::Vector2f size);
	void setState(const std::string& stateName);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void touched(float deltatime) override;
	void affectOther(Entity* other, float deltateim) override;
	int getType() override;
};
