#pragma once
#include <SFML/Graphics.hpp>
#include "../Game/Entities/Entity.h"
#include "Observer.h"
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#define vt sf::Vector2f


class Node : public Observer <Entity> { // (x, y]
public:
	Hitbox space;
	Node* root = nullptr;
	std::vector<std::shared_ptr<Node>> child;
	std::set<Entity*> ens;
	int layer = 0;
	/*
		0: topleft
		1: topright
		2: bottom left
		3: bottom right
	*/

	Node() {
		space = {
			{0, 0},
			{0, 0}
		};
		root = nullptr;
	}

	Node(vt _pos, vt _size) {
		space = { _pos, _size };
		root = nullptr;
	}

	Node(Hitbox box) {
		space = box;
		root = nullptr;
	}

	std::vector <std::shared_ptr<Node>>& subDivide() {
		if (child.size()) return child;
		if (layer >= 5) return child;
		child.resize(4, NULL);
		vt pos = space.pos;
		vt size = space.size / 2.f;
		child[0] = std::make_shared<Node>(pos, size);
		child[1] = std::make_shared<Node>(pos + sf::Vector2f(size.x, 0), size);
		child[2] = std::make_shared<Node>(pos + sf::Vector2f(0, size.y), size);
		child[3] = std::make_shared<Node>(pos + size, size);
		for (auto x : child) x->layer = layer + 1, x->root = root;
	}

	bool contain(Hitbox box) {
		if (box.pos.x < space.pos.x || box.pos.y < space.pos.y) return false;
		box.pos += box.size;
		sf::Vector2f tmp = space.pos + space.size;
		if (tmp.x <= box.pos.x || tmp.y <= box.pos.y) return false;
		return true;
	}

	bool isContainIn(Hitbox box) {
		//std::cout << "checking for " << box.pos.x << ' ' << box.pos.y << ' ' << box.size.x << ' ' << box.size.y << " against " << space.pos.x << ' ' << space.pos.y << ' ' << space.size.x << ' ' << space.size.y << '\n';
		if (box.pos.x > space.pos.x || box.pos.y > space.pos.y) return false;
		box.pos += box.size;
		sf::Vector2f tmp = space.pos + space.size;
		if (tmp.x > box.pos.x || tmp.y > box.pos.y) return false;
		return true;
	}

	void onNotify(Entity* object) override {
		
		if (object->isDead()) {
			ens.erase(object);
			return;
		}
		
		Hitbox temp = object->getHitbox();
		temp.size.x = temp.size.y = 0;
		if (ens.find(object) == ens.end()) return;
		if (contain(temp)) return;
		ens.erase(object);
		object->detach(this);

		vt pos = object->getHitbox().pos;
		vt size = object->getHitbox().size;
		root->insert(pos, object);
	}

	void insert(sf::Vector2f pos, Entity* object) {
		
		if (root == nullptr) {
			ens.insert(object);
			return;
		}

		if (contain({pos, sf::Vector2f(0, 0)}) && layer <= 10) {
			if (child.empty()) subDivide();
			Hitbox tmp = object->getHitbox();
			tmp.size.x = tmp.size.y = 0;
			for (auto ch : child) if (ch->contain(tmp)) {
				ch->insert(pos, object);
				return;
			}

			if (ens.find(object) != ens.end()) {
				return;
			}
			ens.insert(object);
			object->attach(this);
			return;
		}
	}

	void getAll(std::vector <Entity*>& ans) {
		for (auto x : ens) ans.push_back(x);
		for (auto ch : child) ch->getAll(ans);
	}

	bool isIntersect(Hitbox box) {
		if (box.pos.x < space.pos.x + space.size.x &&
			box.pos.x + box.size.x > space.pos.x &&
			box.pos.y < space.pos.y + space.size.y &&
			box.pos.y + box.size.y > space.pos.y) return true;
		return false;
	}

};

class QuadTree {
public:
	std::shared_ptr<Node> root;
	std::shared_ptr<Node> container;
	int m_maxHeight;
	float m_width, m_heigth;

	QuadTree() {
		m_maxHeight = 0;
		m_width = m_heigth = 0;
	}

	void init(float width, float height, int maxHeight) {
		m_width = width, m_heigth = height;
		m_maxHeight = maxHeight;

		Hitbox r = {
			sf::Vector2f(0, 0),
			sf::Vector2f(width, height)
		};

		root = std::make_shared<Node>(r);
		container = std::make_shared<Node>(r);
		root->root = container.get();
	}

	void insert(Entity* en) {
		vt pos = en->getHitbox().pos;
		vt size = en->getHitbox().size;

		root->insert(pos, en);
		root->insert(pos + size, en);
		vt tmp = size;
		tmp.x = 0; size.y = 0;
		root->insert(pos + tmp, en);
		root->insert(pos + size, en);
	}

	void nearEntity(Hitbox space, std::shared_ptr<Node> node, std::vector <Entity*>& ans) {
		if (node->isContainIn(space)) {
			node->getAll(ans);
			return;
		}

		if (node->child.empty()) {
			node->getAll(ans);
			return;
		}

		for (auto ch : node->child) 
			if (ch->isIntersect(space)) {
				nearEntity(space, ch, ans);
			}
		
		if (node->isIntersect(space)) {
			for (auto x : node->ens) ans.push_back(x);
		}

	}

	std::vector <Entity*> nearEntity(Hitbox space) {
		std::vector <Entity*> ans;
		nearEntity(space, root, ans);

		std::sort(ans.begin(), ans.end(), [](Entity* x, Entity* y) {
			return (int)x < (int)y;
		});

		ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
		return ans;
	}

	void checkForPending() {
		for (auto object : container->ens) {
			insert(object);
		}
		container->ens.clear();
	}
};

#undef vt