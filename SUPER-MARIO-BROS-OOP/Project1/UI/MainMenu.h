#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h" 
//#include "../Game/GameController.h"
#include "../Utils/SceneManager.h"
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

class MainMenu
{
private:
    RenderWindow* window = nullptr;
    vector<Button> buttons; // Danh sách các nút
    vector<string> options; // Danh sách các lựa chọn
    vector<Text> texts; // Danh sách các text
    Font font; // Font chữ
    vector<Vector2f> textPositions; // Vị trí của các text
    vector<Vector2f> buttonPositions; // Vị trí của các nút
public:
    MainMenu(RenderWindow* window);
    ~MainMenu();
    Button getButton(int index);
    void init(RenderWindow* window);
    void loopEvents();
    void drawMenu();
    void runMenu();
    RenderWindow* getWindow();
    void setWindow(RenderWindow* window);
};




