#pragma once
#include <vector>
#include <string>

class Zone {
public:
    char type;
    Zone(char t);
};

class GameMap {
public:
    GameMap(int w, int h);
    void generateMap();
    void displayMap();
    // Ajoutez d'autres déclarations de méthodes publiques si nécessaire

private:
    int width, height;
    std::vector<std::vector<Zone>> grid;
    // Déclarations des méthodes privées
};