#pragma once
#include <SFML/Graphics.hpp>

class Physics {
#define vt sf::Vector2f

private:

	vt vel = { 0,0 };
	vt g = { 0, 0 };
	vt fric = { 10, 0 };
	float minGravity = 20;
public:


	Physics(vt vel, vt g) : vel(vel), g(g) {};
	Physics() {};
	Physics getPhysic() {
		return *this;
	}

	void setGravity(vt f);
	void setVel(vt f);
	void setFric(vt f);

	vt getVel() const;
	void performPhysics(float deltaTime);

#undef vt
};
