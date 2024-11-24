#include "Tileset.h"
#include <iostream>
#include "tinyxml2.h" // XML parser library

using namespace tinyxml2;

// Function to load a .tsx file
void Tileset::loadFile(const std::string& s) {
    XMLDocument doc;

    // Load the .tsx file
    if (doc.LoadFile(s.c_str()) != XML_SUCCESS) {
        std::cerr << "Error loading file: " << s << std::endl;
        return;
    }

    // Get the root element (tileset)
    XMLElement* root = doc.FirstChildElement("tileset");
    if (!root) {
        std::cerr << "Error: Root <tileset> element not found in " << s << std::endl;
        return;
    }

    // Extract basic attributes from the tileset
    name = root->Attribute("name");
    root->QueryIntAttribute("tilewidth", &tilewidth);
    root->QueryIntAttribute("tileheight", &tileheight);
    root->QueryIntAttribute("tilecount", &tilecount);
    root->QueryIntAttribute("columns", &columns);

    // Process individual tiles

    int rows = tilecount / columns;
    XMLElement* tile = root->FirstChildElement("tile");

    std::map<std::string, std::vector <std::pair <int, int>>> mpClass;

    while (tile) {
        int id = 0;
        tile->QueryIntAttribute("id", &id);
        int i = id / columns;
        int j = id % columns;
        std::string type = "";
        char* ch = new char[500];
        memset(ch, 0, sizeof ch);

        const char* cch = ch;

        tile->QueryStringAttribute("type", &cch);
        //tile->qe

        type = cch;
        delete[] ch;

        std::string tileName = type + "-" + std::to_string(id);

        mpClass[type].push_back({j * tilewidth , i * tileheight });

        //mp[tileName] = {i * tileheight, j * tilewidth};
        tile = tile->NextSiblingElement("tile");
    }

    for (auto& PII : mpClass) {
        int id = 0;
        std::string type = PII.first + '-';
        for (auto pii : PII.second) 
            mp[type + std::to_string(id++)] = pii;
    }

    std::cout << "Tileset loaded successfully from: " << s << std::endl;
}

// Function to print the tileset details
void Tileset::print() {
    std::cout << "Tileset Name: " << name << std::endl;
    std::cout << "Tile Width: " << tilewidth << std::endl;
    std::cout << "Tile Height: " << tileheight << std::endl;
    std::cout << "Tile Count: " << tilecount << std::endl;
    std::cout << "Columns: " << columns << std::endl;

    std::cout << "Tile Properties:" << std::endl;
    for (const auto x : mp) {
        auto keyx = x.first;
        auto value = x.second;
        std::cout << "Property Name: " << keyx
                  << ", Tile ID: " << value.first
                  << ", Value: " << value.second << std::endl;
    }
}

std::map<std::string, std::vector <std::pair <int, int>>> Tileset::loadMapFromFile(const std::string& s) {
    XMLDocument doc;

    // Load the .tsx file
    if (doc.LoadFile(s.c_str()) != XML_SUCCESS) {
        std::cerr << "Error loading file: " << s << std::endl;
        return std::map<std::string, std::vector <std::pair <int, int>>>();
    }

    // Get the root element (tileset)
    XMLElement* root = doc.FirstChildElement("tileset");
    if (!root) {
        std::cerr << "Error: Root <tileset> element not found in " << s << std::endl;
        return std::map<std::string, std::vector <std::pair <int, int>>>();

    }

    // Extract basic attributes from the tileset
    name = root->Attribute("name");
    root->QueryIntAttribute("tilewidth", &tilewidth);
    root->QueryIntAttribute("tileheight", &tileheight);
    root->QueryIntAttribute("tilecount", &tilecount);
    root->QueryIntAttribute("columns", &columns);

    // Process individual tiles

    int rows = tilecount / columns;
    XMLElement* tile = root->FirstChildElement("tile");

    std::map<std::string, std::vector <std::pair <int, int>>> mpClass;

    while (tile) {
        int id = 0;
        tile->QueryIntAttribute("id", &id);

        int i = id / columns;
        int j = id % columns;

        std::string type = "";
        char* ch = new char[500];
        memset(ch, 0, sizeof ch);

        const char* cch = ch;

        tile->QueryStringAttribute("type", &cch);
        //tile->qe

        type = cch;
        delete[] ch;

        std::string tileName = type;

        mpClass[type].push_back({ j * tilewidth , i * tileheight });

        //mp[tileName] = {i * tileheight, j * tilewidth};
        tile = tile->NextSiblingElement("tile");
    }

    std::cout << "Tileset loaded successfully from: " << s << std::endl;
    return mpClass;
}
