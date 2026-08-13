#pragma once

#include <Util/Timer.h>

class GameManager
{
    enum class State
    {
        GamePlay = 0,
        Pause = 1,
        Length
    };
    
public:
    GameManager();
    ~GameManager() = default;

    inline int GetCurrentScore() const { return score; }
    
private:
    Timer timeLimit;
    int score;
};
