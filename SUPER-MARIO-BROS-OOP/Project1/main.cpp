#include "Game/Game.h"
#include "Game/Scenes/Home/HomeScene.h"
#include "Utils/SceneManager.h"
int main()
{
    //Game& myGame = Game::getInstance();
    //myGame.start();
 
    //while (myGame.isRunning())
    //    myGame.run();

    //myGame.exit();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Scene Manager Test");
    window.setFramerateLimit(60);

    // Access the SceneManager singleton
    SceneManager& sceneManager = SceneManager::getInstance();

    // Create and add a HomeScene
	HomeScene* homeScene = new HomeScene(&window);
	sceneManager.addScene(SceneManager::Scenes::Home, unique_ptr<Scene>(homeScene));

    // Navigate to the HomeScene
    sceneManager.navigateTo(SceneManager::Scenes::Home);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window with a background color
        window.clear(sf::Color::Black);

        // Update and render the current scene
        sceneManager.update();
        sceneManager.render();

        // Display everything drawn to the window
        window.display();
    }

    return 0;
    

    return 0;
}