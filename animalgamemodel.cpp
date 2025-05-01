#include "animalgamemodel.h"
#include "presetgamemode.h"
#include "randomizegamemode.h"
#include <QObject>

/**
 * Implementation of class AnimalGameModel
 * @author Misa de Astis
 * @author Aidan Cooley
 * @version April 21, 2025
 *
 * Reviewed by Marissa Kline
 */

AnimalGameModel::AnimalGameModel(QObject* parent)
    :QObject{parent}
{
    currentLeftAnimal = nullptr;
    currentRightAnimal = nullptr;
    currentWinnerIsLeftAnimal = false;
    userSelectedLeft = false;
    currentJustification = nullptr;
    currentGameMode = nullptr;
}

AnimalGameModel::~AnimalGameModel()
{
    delete currentGameMode;
}

void AnimalGameModel::startGamePreset()
{
    currentGameMode = new PresetGameMode();
    setUpLogic();
    currentLevel = 1;
    userScore = 0;
    emit provideLevel(currentLevel);
}

void AnimalGameModel::startGameRandom()
{
    currentGameMode = new RandomizeGameMode();
    setUpLogic();
    currentLevel = 1;
    userScore = 0;
    emit provideLevel(currentLevel);
}

void AnimalGameModel::setUpLogic()
{
    currentLeftAnimal =  currentGameMode->provideLeftOpponent();
    currentRightAnimal = currentGameMode->provideRightOpponent();
    currentWinnerIsLeftAnimal = currentGameMode->provideWinner();
    currentJustification = currentGameMode->provideJustification();

    //send all the new info to view
    emit provideLeftAnimal(currentLeftAnimal);
    emit provideRightAnimal(currentRightAnimal);
    emit provideWinner(currentWinnerIsLeftAnimal);
    emit provideJustification(currentJustification);
}

void AnimalGameModel::nextLevel()
{
    //1 if we are done with matchups, 0 otherwise
    int gameEnded = currentGameMode->nextLevel();

    if(gameEnded){
        //end game logic
        emit endGameStats(userScore);
        return;
    }
    //if not at the end, continue normally
    setUpLogic();
    currentLevel++;
    emit provideLevel(currentLevel);
}

void AnimalGameModel::clickedLeftAnimal()
{
    userSelectedLeft = true;
}

void AnimalGameModel::clickedRightAnimal()
{
    userSelectedLeft = false;
}

void AnimalGameModel::finalWinnerSelected()
{
    //If user is correct
    if((userSelectedLeft && currentWinnerIsLeftAnimal)
        || (!userSelectedLeft && !currentWinnerIsLeftAnimal))
    {
        userScore++;
        emit userCorrect(true);
        return;
    }
    emit userCorrect(false);
}

void AnimalGameModel::endGame()
{
    delete currentGameMode;
}

void AnimalGameModel::restartGame(){
    if (typeid(*currentGameMode) == typeid(RandomizeGameMode)){
        startGameRandom();
    }
    else{
        startGamePreset();
    }
}





