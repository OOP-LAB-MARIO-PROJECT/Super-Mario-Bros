#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class Observer {
	std::vector <Observer*> obs;
public:
	virtual ~Observer() = default;

	void attach(Observer* ob) {
		for (auto x : obs) if (x == ob) return;
		obs.push_back(ob);
	}

	void detach(Observer* ob) {
		int i = 0;
		for (; i < obs.size(); i++) if (obs[i] == ob) {
			obs.erase(obs.begin() + i);
			return;
		}
	}

	void notify(T* object) {
		for (auto o : obs) o->onNotify(object);
	}

	virtual void onNotify(T* updatedObject) {};
};

