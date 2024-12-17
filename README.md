
# SUPER MARIO BROS - OOP

Welcome to the **Super Mario Bros - OOP** project! This is a class project for demonstrating object-oriented programming (OOP) principles in the context of game development. The project implements a simplified version of the Mario game using a structured and modular design.

---

## 📂 Project Structure

Here is an overview of the directory structure and its purpose:

```
SUPER-MARIO-BROS-OOP/
├── .git/                              # Git version control files
├── dependencies/                      # External dependencies and libraries
├── Project1/
    ├── Assets/                        # Game assets including sounds and textures
        ├── Sounds/                    # Audio files for the game
            ├── SoundFile1/
            ├── ...
            ├── sound_interface.txt    # interface for adding new sounds
        ├── Textures/                  # Images and textures used in the game
            ├── Texture1/
            ├── ...
            ├── texture_interface.txt  # interface for adding new textures
        ├── Fonts/                     # Fonts used in the game
    ├── Game/                          # Core game logic and components
        ├── Components/                # Reusable game components
        ├── Control/                   # Input handling and game controls
        ├── Entities/                  # Entity classes like Mario, enemies, etc.
        ├── Scenes/                    # Game scenes
            ├── Game/                  # Gameplay scene
            ├── Home/                  # Home menu scene
            ├── Setting/               # Settings menu scene
            ├── Exit/                  # Settings menu scene
            ├── Login/                 # Settings menu scene
            ├── Register/              # Settings menu scene
        ├── Utils/                     # Utility functions and helper classes
    ├── UI/                            # Utility functions and helper classes

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
- **Exit Scene**: Allows the player to exit the game.
- **Login Scene**: Allows the player to login.
- **Register Scene**: Allows the player to register.
- **Game Over Scene**: Displays the game over screen.

Each scene is managed independently in the `/Scenes/` directory for modularity.

---

## 📂 Assets

All assets are stored in the `Assets/` directory:

- **Sounds**: Contains audio files like background music and sound effects.
- **Fonts**: Includes fonts used in the game.
- **Textures**: Stores sprite sheets and game textures.

### Interface for Adding New Assets
- **Sounds**: To add new sounds, follow the interface in `Assets/Sounds/sound_interface.txt`.
   **Example:** the first column is the name of the sound and the second column is the path to the sound file.
```
background Sound_Pack/background.wav
collect Sound_Pack/collect.wav
defeat Sound_Pack/defeat.wav
hit Sound_Pack/hit.wav
jump Sound_Pack/jump.wav
```


- **Textures**: To add new textures, follow the interface in `Assets/Textures/texture_interface.txt`.
   **Example:** the first column is the name of the tilemap file and the second column is the path to the texture file.
```
Texture_Pack/mario.tsx Texture_Pack/mario.png
```
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

# CÁC TÍNH NĂNG YÊU CẦU NHƯNG CHƯA LÀM

- [ ] Chiến thắng -> đu cột cờ
- [x] Qua màn -> animantion cho mario -> del lam
- [x] Xuống cống -> thiếu animation 
- [x] Special Platform -> mấy cái platform di chuyển -> ok
- [x] Enemy -> oki -> nhưng còn thiếu enemi
- [x] Biến lớn nhỏ
- [x] Chết animation -> ok
- [x] Player -> behavior
- [ ] Scene chọn màn chơi
- [ ] Power - up
- [x] Save Game/ Load Game -> oki
- [ ] Background
- [ ] UI -> ok -> chỉnh them cho scale
- [ ] projectile -> player



- [x] Boss
- [ ] Vòng lửa
- [ ] gạch chứa vàng
- [ ] nhạc game
- [x] phá block
- [ ] nền
- [ ] cờ 
- [ ] lò xo