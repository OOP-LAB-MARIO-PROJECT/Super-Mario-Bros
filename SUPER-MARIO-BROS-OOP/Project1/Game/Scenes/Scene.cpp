#include "Scene.h"

Scene::Scene(sf::RenderWindow* window) : window(window) {};
void Scene::display() {
	window->display();
}

const sf::RenderWindow* Scene::getWindow() const {
	return window;
}