#include "randomizegamemode.h"
#include <QFile>
#include <QTextStream>

/**
 * Implementation of class RandomizeGameMode
 * @author Misa de Astis
 * @author Aidan Cooley
 * @version April 21, 2025
 *
 * Reviewed by John Radford
 */

RandomizeGameMode::RandomizeGameMode()
{
    readInAnimals(QFile(":/textFiles/animalFacts"));
    readInAnimalRanks(QFile(":/textFiles/animalRanks"));
    chooseMatchUp();
    currentLevel = 1;
    currentWinner = nullptr;
}

void RandomizeGameMode::readInAnimals(QFile file)
{
    animalList = QList<Animal*>();
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //failed
        return;
    }

    QString name;
    QString height;
    QString weight;
    QString heightSub;
    QString weightSub;
    QVector<QString> strengths = QVector<QString>();
    QString weakness;

    QTextStream in(&file);

    while(!in.atEnd())
    {
        //first 3 attributes of an animal
        name = in.readLine();
        height = in.readLine();
        heightSub = height.mid(7);
        weight = in.readLine();
        weightSub = weight.mid(7);

        //skip the generic "Strengths:" line
        in.readLine();

        //get three strengths
        strengths.append(in.readLine());
        strengths.append(in.readLine());
        strengths.append(in.readLine());

        //skip the generic "Weakness:" line
        in.readLine();
        //get the weakness
        weakness = in.readLine();

        Animal *nextAnimal = new Animal(name, heightSub, weightSub, strengths, weakness);

        animalList.append(nextAnimal);

        //clear strength list
        strengths.clear();
    }
}

void RandomizeGameMode::readInAnimalRanks(QFile file)
{
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QString name;
    float rank;
    QTextStream in(&file);

    while(!in.atEnd())
    {
        bool ok;
        name = in.readLine();
        rank = in.readLine().toFloat(&ok);
        animalRanks[name] = rank;
    }
}

void RandomizeGameMode::chooseMatchUp()
{
    //use random obj
    std::mt19937 gen(randomIntGenerator());
    std::uniform_int_distribution<> dis(0,59);
    int leftAnimalIndex = dis(gen);
    int rightAnimalIndex = dis(gen);
    if(leftAnimalIndex == rightAnimalIndex){
        rightAnimalIndex = dis(gen);
    }

    currentLeftOpponent = animalList[leftAnimalIndex];
    currentRightOpponent = animalList[rightAnimalIndex];

    findWinner();
}

void RandomizeGameMode::findWinner()
{
    float leftRank = animalRanks[currentLeftOpponent->getName()];

    float rightRank = animalRanks[currentRightOpponent->getName()];

    if(leftRank > rightRank)
    {
        currentWinner = currentLeftOpponent;
        currentWinnerIsLeft = true;
    }else
    {

        currentWinner = currentRightOpponent;
        currentWinnerIsLeft = false;
    }
    editCurrentJustification();
}

void RandomizeGameMode::editCurrentJustification()
{
    //create random
    //use random obj
    std::mt19937 gen(randomIntGenerator());
    std::uniform_int_distribution<> dis(0,2);

    int selectedAdLib = dis(gen);

    switch(selectedAdLib){
    case 0:
        createAdLibOne();
        break;
    case 1:
        createAdLibTwo();
        break;
    case 2:
        createAdLibThree();
        break;
    }
}

void RandomizeGameMode::createAdLibOne()
{
    QString winnerName = currentWinner->getName();
    QString winnerStrengths = currentWinner->getStrengths().join(", ").toLower();
    buildStr = "The winner is " + winnerName + "! Did you know that " + winnerName + " is about" + currentWinner->getHeight() +
    " feet tall and weighs" + currentWinner->getWeight() + "? Pretty interesting right?! Some strengths that the " + winnerName +
                          " has are " + winnerStrengths + "! ";
    currentJustification = &buildStr;

}

void RandomizeGameMode::createAdLibTwo()
{
    QString winnerName = currentWinner->getName();
    QString winnerStrengths = currentWinner->getStrengths().join(", ").toLower();
    buildStr = "Wow that was a close one! In the end the " + winnerName + " won out. Did you know that the " + winnerName +
    " has the strengths: " + winnerStrengths + "? This really helped it win in the crazy fight of "
                          + currentLeftOpponent->getName() + " vs " + currentRightOpponent->getName() + ".";

    currentJustification = &buildStr;
}

void RandomizeGameMode::createAdLibThree()
{
    QString winnerName = currentWinner->getName();
    QString winnerStrengths = currentWinner->getStrengths().join(", ").toLower();
    buildStr = "In the giant animal colosseum with the match up of " + currentLeftOpponent->getName() + " and "
    + currentRightOpponent->getName() + " the winner is......... " + winnerName + "!!! " + " The strengths of " + winnerName +
               " are " + winnerStrengths + ". These strengths led it to victory!";

    currentJustification = &buildStr;
}

int RandomizeGameMode::nextLevel()
{
    if(currentLevel == 30)
    {
        //return 1 if done
        return 1;
    }
    chooseMatchUp();
    currentLevel++;

    return 0;
}

RandomizeGameMode::~RandomizeGameMode()
{
    qDeleteAll(animalList);
    animalList.clear();
}

