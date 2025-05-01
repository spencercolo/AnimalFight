#include "gamemode.h"

/**
 * Implementation of class GameMode
 * @author John Radford
 * @author Marissa Kline
 * @version April 21, 2025
 *
 * Reviewed Spencer Cologna
 */

GameMode::GameMode() { }

GameMode::~GameMode() { }

const Animal* GameMode::provideLeftOpponent() const
{
    return currentLeftOpponent;
}

const Animal* GameMode::provideRightOpponent() const
{
    return currentRightOpponent;
}

const QString* GameMode::provideJustification() const
{
    return currentJustification;
}

bool GameMode :: provideWinner() const
{
    return currentWinnerIsLeft;
}

int GameMode :: getCurrentLevel() const
{
    return currentLevel;
}
