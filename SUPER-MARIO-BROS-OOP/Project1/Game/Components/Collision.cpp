#include "Collision.h"

#define vt sf::Vector2f
bool Collision::pointVsRect(const vt& p, const rect& r) {
	int x = r.getPosition().x;
	int y = r.getPosition().y;
	int w = r.getSize().x;
	int h = r.getSize().y;
	return (p.x >= x && p.x < x + w && p.y >= y && p.y <= y + h);
}


bool Collision::rectVsRect(const rect& r1, const rect& r2) {
	return (
		r1.pos.x < r2.pos.x + r2.size.x &&
		r1.pos.x + r1.size.x > r2.pos.x &&
		r1.pos.y < r2.pos.y + r2.size.y &&
		r1.pos.y + r1.size.y > r2.pos.y
		);
}

bool Collision::rayVsRect(const vt& rayOrigin, const vt& rayDir,
	const rect& target,
	vt& contactNormal,
	vt& contactPoint,
	float& tHitNear) {

	contactNormal = { 0, 0 };
	contactPoint = { 0, 0 };

	if (rayDir == vt{ 0, 0 }) return false;

	vt invDir = vt(1 / rayDir.x, 1 / rayDir.y);


	vt O = target.getPosition() - rayOrigin;
	vt B = target.getPosition() + target.getSize() - rayOrigin;

	vt tNear = vt(O.x * invDir.x, O.y * invDir.y);
	vt tFar = vt(B.x * invDir.x, B.y * invDir.y);

	if (std::isnan(tFar.y) || std::isnan(tFar.x)) return false;
	if (std::isnan(tNear.y) || std::isnan(tNear.x)) return false;

	if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
	if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);
	// Early rejection		
	if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

	tHitNear = std::max(tNear.x, tNear.y);

	float tHitFar = std::min(tFar.x, tFar.y);

	if (tHitFar < 0) return false;

	//std::cout << "contact Time " << tHitNear << '\n';

	// Contact point of collision from parametric line equation
	//contact_point = ray_origin + t_hit_near * ray_dir;

	contactPoint = rayOrigin + tHitNear * rayDir;


	if (tNear.x > tNear.y)
		if (invDir.x < 0)
			contactNormal = { 1, 0 };
		else
			contactNormal = { -1, 0 };
	else if (tNear.x < tNear.y)
		if (invDir.y < 0)
			contactNormal = { 0, 1 };
		else
			contactNormal = { 0, -1 };
	return true;
}

bool Collision::dynamicRectVsRect(const rect& rDynamic, const float fTimeStep, const rect& rStatic,
	vt& contactPoint, vt& contactNormal, float& contactTime
) {

	if (rDynamic.vel.x == 0 && rDynamic.vel.y == 0) return false;

	rect expandedTarget;
	expandedTarget.pos = rStatic.pos - vt(rDynamic.size.x / 2, rDynamic.size.y / 2);
	expandedTarget.size = rStatic.size + rDynamic.size;

	if (
		rayVsRect(rDynamic.pos + vt(rDynamic.size.x / 2, rDynamic.size.y / 2),
			rDynamic.vel * fTimeStep, expandedTarget, contactNormal, contactPoint, contactTime)
		)
		return (contactTime >= 0.0f && contactTime < 1.0f);
	return false;
}

bool Collision::resolveDynamicRectVsRect(rect& r_dynamic, const float fTimeStep, rect& r_static, vt& pushback)
{
	vt contact_point = { 0, 0 }, contact_normal = { 0, 0 };
	float contact_time = 0.0f;
	if (dynamicRectVsRect(r_dynamic, fTimeStep, r_static, contact_point, contact_normal, contact_time))
	{
		if (contact_normal.y > 0) r_dynamic.contact[0] = &r_static; else  r_dynamic.contact[0] = nullptr;
		if (contact_normal.x < 0) r_dynamic.contact[1] = &r_static; else  r_dynamic.contact[1] = nullptr;
		if (contact_normal.y < 0) r_dynamic.contact[2] = &r_static; else  r_dynamic.contact[2] = nullptr;
		if (contact_normal.x > 0) r_dynamic.contact[3] = &r_static; else  r_dynamic.contact[3] = nullptr;

		vt a = vt(std::abs(r_dynamic.vel.x), std::abs(r_dynamic.vel.y));
		r_dynamic.pos += vt(a.x * contact_normal.x, a.y * contact_normal.y) * (1 - contact_time) * fTimeStep;
		pushback += vt(a.x * contact_normal.x, a.y * contact_normal.y) * (1 - contact_time);
		//std::cout << "wh is true: " << r_dynamic.pos.x << ' ' << r_dynamic.pos.y << '\n';;
		return true;
	}

	return false;
}

vt Collision::rectVsTerain(Hitbox dynamicRect, std::vector <Hitbox> ground, vt vel, float deltaTime, vt& pos, int& direction) {

	rect dr = { dynamicRect.pos, dynamicRect.size, vel };
	dr.pos = dynamicRect.pos;
	dr.size = dynamicRect.size;
	dr.vel = vel;
	//std::cout << vel.x << ' ' << vel.y << '\n';
	std::vector<std::pair <rect, float>> z;

	vt ifCollide = { 0, 0 };

	for (const Hitbox& rec : ground) {
		vt cp, cn;
		float ct;
		rect tmp;
		tmp.size = rec.size;
		tmp.pos = rec.pos;

		if (dynamicRectVsRect(dr, deltaTime, tmp, cp, cn, ct))
			z.emplace_back(tmp, ct);
	}


	std::sort(z.begin(), z.end(), [](const std::pair<rect, float>& a, const std::pair<rect, float>& b)
		{
			return a.second < b.second;
		});

	if (z.empty()) return vel;
	for (std::pair<rect, float>& j : z) {
		resolveDynamicRectVsRect(dr, deltaTime, j.first, vel);
	}



	pos = dr.pos;
	direction = 0;

	for (int i = 0; i < 4; i++)
		if (dr.contact[i] != nullptr)
			direction |= 1 << i;

	return vel;
}


dir Collision::getDir(std::array<Collision::rect*, 4> contact) {
	if (contact[2]) return dir::TOP;
	if (contact[1]) return dir::LEFT;
	if (contact[0]) return dir::BOTTOM;
	if (contact[3]) return dir::RIGHT;
	return NO_COLLIDE;
}

dir Collision::dirDynamicRectVsRect(const rect& rDynamic, const float fTimeStep, const rect& rStatic) {

	vt cp, cn;
	float ct;
	if (!dynamicRectVsRect(rDynamic, fTimeStep, rStatic, cp, cn, ct)) return NO_COLLIDE;
	rect rd = rDynamic, rs = rStatic;
	resolveDynamicRectVsRect(rd, fTimeStep, rs, cn);

	return getDir(rd.contact);
}

dir Collision::dynamicRectVsRect(const Hitbox& dynamicRect, const float fTimeStep, const vt& vel, const Hitbox& staticRect) {
	
	rect dRect = {
		dynamicRect.pos,
		dynamicRect.size,
		vel
	};

	rect sRect = {
		staticRect.pos,
		staticRect.size
	};

	return dirDynamicRectVsRect(dRect, fTimeStep, sRect);
}


#undef vt

