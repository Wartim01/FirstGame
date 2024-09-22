#include "Game.h"
#include <iostream>

Game::Game() : isRunning(true) {
    Init();
}

Game::~Game() {}

void Game::Init() {
    std::cout << "Initialisation du jeu...\n";
    // Init des composants : personnages, calendrier, événements, etc.
}

void Game::Update(float deltaTime) {
    gameCalendar.Update(deltaTime);  // Mise à jour du calendrier
    eventManager.Update();  // Mise à jour des événements
}

void Game::Render() {
    // Render de la scène, HUD, etc.
}

void Game::HandleInput() {
    // Gestion des entrées clavier/souris
}

void Game::Run() {
    float deltaTime = 0.016f;  // Par exemple, pour 60 FPS
    while (isRunning) {
        HandleInput();
        Update(deltaTime);
        Render();
    }
}

int main() {
    std::cout << "Jeu démarré!" << std::endl;
    return 0;
}