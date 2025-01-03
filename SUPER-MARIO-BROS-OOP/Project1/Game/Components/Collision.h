#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../Entities/Entity.h"

enum dir {
	TOP = 0,
	LEFT = 1,
	BOTTOM = 2,
	RIGHT = 3,
	NO_COLLIDE = -1
};

class Collision {
#define vt sf::Vector2f
public:

	struct rect {
		vt pos;
		vt size;
		vt vel = { 0, 0 };

		std::array<Collision::rect*, 4> contact;

		vt getPosition() const { return pos; };
		vt getSize() const { return size; };
		vt getVel() const { return vel; };

	};

	bool pointVsRect(const vt& p, const rect& r);
	bool rectVsRect(const rect& r1, const rect& r2);

	bool rayVsRect(const vt& rayOrigin, const vt& rayDir, const rect& target, vt& contactNormal, vt& contactPoint, float& tHitNear);

	bool dynamicRectVsRect(const rect& rDynamic, const float fTimeStep, const rect& rStatic,
		vt& contactPoint, vt& contactNormal, float& contactTime
	);
	

	bool resolveDynamicRectVsRect(rect& r_dynamic, const float fTimeStep, rect& r_static, vt& pushback);

	/*
	* take an origin rectangle 'o', then resolve it with a vector of rectangles v
	* remember to put in deltatime
	*/


	/*
	* 	if (contact[2]) return dir::TOP;
		if (contact[1]) return dir::LEFT;
		if (contact[0]) return dir::BOTTOM;
		if (contact[3]) return dir::RIGHT;

		1 << 0: BOTTOM
		1 << 1: LEFT
		1 << 3: RIGHT
		1 << 2: TOP
	*/
	vt rectVsTerain(Hitbox dynamicRect, std::vector <Hitbox> ground, vt vel, float deltaTime, vt& pos, int& direction);



	enum dir getDir(std::array<Collision::rect*, 4> contact);

	// return the direction of contact, used for Collision::rect
	enum dir dirDynamicRectVsRect(const rect& rDynamic, const float fTimeStep, const rect& rStatic);

	/*
		return the direction of contact, used for sf::RectangleShape
		
		enum dir {
			TOP = 1,
			LEFT = 2,
			BOTTOM = 3,
			RIGHT = 4,
			NO_COLLIDE = -1
		};
	
	*/ 
	dir dynamicRectVsRect(const Hitbox& dynamicRect, const float fTimeStep, const vt& vel, const Hitbox& staticRect);
	dir dynamicRectVsRect(const Hitbox& dynamicRect, const float fTimeStep, const vt& vel, const Hitbox& staticRect, sf::Vector2f& pushback);
#undef vt
};