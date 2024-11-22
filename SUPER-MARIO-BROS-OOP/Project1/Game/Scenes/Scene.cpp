#include "Scene.h"
#include <iostream>
#include <exception>

Scene::Scene(sf::RenderWindow* window) : window(window) {};
void Scene::display() {
	window->display();
}

sf::RenderWindow* Scene::getWindow() {
	return window;
}

Scene::Scene() {
	throw std::exception("Can not create a scene with no window initialize\n");
}
