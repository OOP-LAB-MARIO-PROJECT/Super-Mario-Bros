#include "Game.h"
#include <sstream> // For creating strings

Game::~Game() {
    delete window;
};

void Game::start() {
    // Basic window setup -> will change after
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int screenWidth = desktop.width / 8;

    window = new sf::RenderWindow(sf::VideoMode(screenWidth * 5, screenWidth * 3), "Mario");
    window->setFramerateLimit(60);
    m_clock.restart();

    // Load resources
    textureManager = &TextureManager::getInstance();
    textureManager->loadFromInterface("Assets/Textures/texture_interface.txt");

    soundManager = &SoundManager::getInstance();
    soundManager->loadFromInterface("Assets/Sounds/sound_interface.txt");

    fontManager = &FontManager::getInstance();
    fontManager->loadFromInterface("Assets/Fonts/font_interface.txt");

    sceneManager = &SceneManager::getInstance();

    sceneManager->addScene(SceneManager::Scenes::Login, new LoginScene(window));
    sceneManager->addScene(SceneManager::Scenes::Register, new RegisterScene(window));
    sceneManager->addScene(SceneManager::Scenes::Home, new HomeScene(window));
    sceneManager->addScene(SceneManager::Scenes::Exit, new ExitScene(window));
    sceneManager->addScene(SceneManager::Scenes::Game, new GameScene(window));
    sceneManager->addScene(SceneManager::Scenes::Setting, new SettingScene(window));

    sceneManager->navigateTo(SceneManager::Scenes::Game);

    // Truy cập và thay đổi cài đặt ban đầu
    GameConfig& config = GameConfig::getInstance();
    config.setPlayerName("Hero");
    config.setCurrentLevel("Level 1");
    config.setVolume(75.0f);
    config.updateControl("MoveLeft", sf::Keyboard::Left); // Đổi phím di chuyển trái

    m_isRunning = true;
};

void Game::run() {
    if (!window->isOpen()) {
        m_isRunning = false;
        return;
    }

    float deltatime = m_clock.restart().asSeconds();

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }

    // Get game configuration instance
    GameConfig& config = GameConfig::getInstance();

    // Set up text objects to display information
    const sf::Font& font = *(fontManager->getFont("default"));
    sf::Text playerNameText("Player: " + config.playerName, font, 20);
    sf::Text levelText("Level: " + config.currentLevel, font, 20);
    sf::Text scoreText("Score: " + std::to_string(config.score), font, 20);
    sf::Text coinText("Coins: " + std::to_string(config.coins), font, 20);
    sf::Text timeText("Time: " + std::to_string(config.timeLeft) + "s", font, 20);
    sf::Text volumeText("Volume: " + std::to_string(config.volume), font, 20);

    // Position the text
    playerNameText.setPosition(10, 10);
    levelText.setPosition(10, 40);
    scoreText.setPosition(10, 70);
    coinText.setPosition(10, 100);
    timeText.setPosition(10, 130);
    volumeText.setPosition(10, 160);

    // Update game logic
    sceneManager->update(deltatime);

    // Render
    window->clear();
    sceneManager->render(); // Render the current scene

    window->display();
};

void Game::exit() {
    window->close();
};

bool Game::isRunning() const {
    return m_isRunning;
};
