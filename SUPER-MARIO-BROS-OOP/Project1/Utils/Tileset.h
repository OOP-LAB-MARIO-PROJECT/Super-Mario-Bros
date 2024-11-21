#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Tileset {
public:

    std::string name;
    int tilewidth;
    int tileheight;
    int tilecount;
    int columns;

    std::map<std::string, std::pair <int, int>> mp;


    void loadFile(const std::string& s);
    void print();

};