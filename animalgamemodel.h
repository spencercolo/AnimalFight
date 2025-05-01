#ifndef ANIMALMODEL_H
#define ANIMALMODEL_H

#include <QObject>
#include <QWidget>
#include "animal.h"
#include "gamemode.h"

/**
 * @brief This class is the backend for the game. It interacts with the gameMode below it and the mainWindow view above it
 * @author Misa Nieto
 * @author Aidan Cooley
 * @version April 21, 2025
 *
 * Reviewed by Marissa Kline
 */
class AnimalGameModel : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief AnimalGameModel constructor that takes in a QObject
     * as it's parent to associate to view
     * @param parent - the view if necessary
     */
    AnimalGameModel(QObject *parent = nullptr);

    /**
     * Deconstruct the model
     */
    ~AnimalGameModel();

signals:

    /**
     * @brief Sends the left animal of the next matchup
     * @param the next left animal
     */
    void provideLeftAnimal(const Animal *left);

    /**
     * @brief Sends the right animal of the next matchup
     * @param the next right animal
     */
    void provideRightAnimal(const Animal *right);

    /**
     * @brief sends true if the left animal wins the next matchup, false otherwise
     * @param the boolean stating if the left animal wins the matchup
     */
    void provideWinner(bool winnerIsLeft);

    /**
     * @brief Sends the blurb of why the given animal would win the matchup
     * @param the string describing the justification
     */
    void provideJustification(const QString *justification);

    /**
     * @brief sends the end game score of the user
     * @param finalUserScore, the final score
     */
    void endGameStats(int finalUserScore);

    /**
     * @brief sends the current level the user is on
     * @param level, the current level
     */
    void provideLevel(int level);

    /**
     * @brief Sends if the user guest right to the view
     * @param true if the user guessed correcty, false otherwise
     */
    void userCorrect(bool correct);

public slots:

    /**
     * @brief Sets the gameMode based off of what the user chooses on menu
     */
    void startGamePreset();

    /**
     * @brief Sets the gameMode based off of what the user chooses on menu
     */
    void startGameRandom();

    /**
     * @brief Advancing the game to the next level
     */
    void nextLevel();

    /**
     * @brief Shows score at the end of the game
     */
    void endGame();

    /**
     * @brief Receive the users input and check against answer
     */
    void clickedLeftAnimal();

    /**
     * @brief Receive the users input and check against answer
     */
    void clickedRightAnimal();

    /**
     * @brief Receive the users input of final answer
     */
    void finalWinnerSelected();

    /**
     * @brief Restarts the game depending on the current game mode
     */
    void restartGame();

private:

    /**
     * @brief The left animal of this mathc up
     */
    const Animal *currentLeftAnimal;

    /**
     * @brief The right animal of this matchup
     */
    const Animal *currentRightAnimal;

    /**
     * @brief true if the left animal of this matchup would win the fight, false if the right animal would
     */
    bool currentWinnerIsLeftAnimal;

    /**
     * @brief The current level that the user is on
     */
    int currentLevel;

    /**
     * @brief The small blurb about why the winning animal would win in a fight
     */
    const QString *currentJustification;

    /**
     * @brief The curreht game mode chosen by the user, impacts which animals are displayed in what order
     */
    GameMode *currentGameMode;

    /**
     * @brief The current number of correct guesses from the user
     */
    int userScore;

    /**
     * @brief Establishes logic for the game
     */
    void setUpLogic();

    /**
     * @brief Indicates what the user selected
     */
    bool userSelectedLeft;
};

#endif // ANIMALMODEL_H
