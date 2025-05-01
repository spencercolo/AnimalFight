#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "animal.h"
#include <QString>

/**
 * @brief The GameMode class- this class will be derived from for the 2 Game Modes, Preset and Random
 * @author John Radford
 * @author Marissa Kline
 * @version April 21, 2025
 *
 * Reviewed by Spencer Cologna
 */
class GameMode{

public:

    /**
     * @brief provideLeftOpponent - provides the animal on the left of the current matchup
     * @return Animal object
     */

    const Animal* provideLeftOpponent() const;

    /**
     * @brief provideRightOpponent - provides the animal on the right of the current matchup
     * @return
     */
    const Animal* provideRightOpponent() const;

    /**
     * @brief provideWinner - provides the animal whom is the winner of the current matchup
     * @return boolean
     */
    bool provideWinner() const;

    /**
     * @brief getCurrentLevel - gets the current level
     * @return int
     */
    int getCurrentLevel() const;

    /**
     * @brief provideJustification - provides the justification of why the current winner of the matchup was chosen
     * @return
     */
    const QString* provideJustification() const;

    /**
     * @brief nextLevel - represents progressing through internal structures to show next level state. Returns 0 if
     * game continues or 1 if over.
     */
    virtual int nextLevel() = 0;

    /**
     * @brief GameMode - constructor to initialize an instance of this object
     */
    GameMode();

    /**
     * @brief ~GameMode - deconstructor to clean up internal object data
     */
    virtual ~GameMode();


protected:

    /**
     * @brief currentLeftOpponent - private instance variable to represent the left anmial of the current matchup
     *
     */
    const Animal* currentLeftOpponent;

    /**
     * @brief currentRightOpponent - private instance variable to represent the right anmial of the current matchup
     */
    const Animal* currentRightOpponent;

    /**
     * @brief currentWinnerIsLeft - boolean to represent the victor of the current matchup
     */
    bool currentWinnerIsLeft;

    /**
     * @brief currentLevel - int representation of the current level
     */
    int currentLevel;

    /**
     * @brief currentJustification - representation of the justification in favor of the winning animal in the matchup
     */
    const QString* currentJustification;
};

#endif // GAMEMODE_H
