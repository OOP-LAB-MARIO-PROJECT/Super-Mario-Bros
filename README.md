
# SUPER MARIO BROS - OOP

Welcome to the **Super Mario Bros - OOP** project! This is a class project for demonstrating object-oriented programming (OOP) principles in the context of game development. The project implements a simplified version of the Mario game using a structured and modular design.

---

## 📂 Project Structure

Here is an overview of the directory structure and its purpose:

```
SUPER-MARIO-BROS-OOP/
├── .git/                   # Git version control files
├── dependencies/           # External dependencies and libraries
├── Project1/
    ├── Assets/             # Game assets including sounds and textures
        ├── Sounds/         # Audio files for the game
        ├── Textures/       # Images and textures used in the game
    ├── Game/               # Core game logic and components
        ├── Components/     # Reusable game components
        ├── Entities/       # Entity classes like Mario, enemies, etc.
        ├── Scenes/         # Game scenes
            ├── Game/       # Gameplay scene
            ├── Home/       # Home menu scene
            ├── Setting/    # Settings menu scene
        ├── Utils/          # Utility functions and helper classes
```

---

## 🚀 Features

- **OOP Principles**: The project is designed with encapsulation, inheritance, polymorphism, and abstraction in mind.
- **Modular Design**: Each component is encapsulated in its own directory for easy maintenance and scalability.
- **Custom Assets**: Includes sound effects and textures to enhance the gameplay experience.
- **Scene Management**: Multiple scenes including the main gameplay, home menu, and settings.

---

## 🛠️ Dependencies

Make sure you have the following dependencies installed:

- **Game Development Framework**: Specify the library or framework you used (e.g., SFML, Pygame, Unity, etc.)
- **Programming Language**: [Your language, e.g., C++, Python, etc.]

Instructions for installing dependencies can be found in the `/dependencies/` directory.

---

## 🔧 How to Run

1. Clone this repository:
   ```bash
   git clone https://github.com/your-repo/super-mario-bros-oop.git
   ```

2. Navigate to the project folder:
   ```bash
   cd SUPER-MARIO-BROS-OOP/Project1
   ```

3. Build or run the project:
   - [Instructions for your build process, e.g., using `make`, an IDE, or running a script]

---

## 📖 OOP Concepts in Action

This project demonstrates the following OOP concepts:

1. **Encapsulation**:
   - Game entities like Mario, enemies, and items are encapsulated within the `Entities/` folder.
   - Reusable utilities and helpers are located in the `Utils/` folder.

2. **Inheritance**:
   - Common functionality is shared between game components using inheritance.

3. **Polymorphism**:
   - Different entities (e.g., Mario and enemies) override common methods to implement specific behaviors.

4. **Abstraction**:
   - Abstract classes or interfaces are used for game components and entities to enforce a unified design.

---

## 🎮 Gameplay

The game includes the following scenes:

- **Home Scene**: Displays the main menu.
- **Game Scene**: The core gameplay environment.
- **Settings Scene**: Allows the player to adjust settings.

Each scene is managed independently in the `/Scenes/` directory for modularity.

---

## 📂 Assets

All assets are stored in the `Assets/` directory:

- **Sounds**: Contains audio files like background music and sound effects.
- **Textures**: Stores sprite sheets and game textures.

---

## 🖥️ Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bugfix:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes and push the branch:
   ```bash
   git commit -m "Description of feature"
   git push origin feature-name
   ```
4. Open a pull request.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute this project.

---

## 👩‍🏫 About

This project was created as part of an Object-Oriented Programming class assignment at [Your University Name]. It demonstrates game development concepts in an academic setting.


[]: # (End of README.md)