#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include "Calendar.h"
#include "EventManager.h"

class Game {
public:
    Game();
    ~Game();

    void Init();
    void Update(float deltaTime);
    void Render();
    void HandleInput();
    void Run();

private:
    Calendar gameCalendar;
    EventManager eventManager;
    bool isRunning;
};

#endif // GAME_H
