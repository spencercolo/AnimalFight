#ifndef RANDOMIZEGAMEMODE_H
#define RANDOMIZEGAMEMODE_H

#include "gamemode.h"
#include <QFile>
#include <unordered_map>
#include <random>

/**
 * @brief The RandomizeGameMode class - Controls the information setup for the Randomized Matchups Game Mode; derived class of GameMode
 * @author Misa De Astis
 * @author Aidan Cooley
 * @version April 21, 2025
 */
class RandomizeGameMode : public GameMode{
public:

    RandomizeGameMode();
    ~RandomizeGameMode();

    /**
     * @brief provideLeftOpponent - provides the animal on the left of the current matchup
     * @return Animal object
     */
    Animal* provideLeftOpponent();

    /**
     * @brief provideRightOpponent - provides the animal on the right of the current matchup
     * @return
     */
    Animal* provideRightOpponent();

    /**
     * @brief provideWinner - provides the animal whom is the winner of the current matchup
     * @return
     */
    bool provideWinner() const;

    /**
     * @brief provideJustification - provides the justification of why the current winner of the matchup was chosen
     * @return
     */
    QString *provideJustification() const;

    /**
     * @brief nextLevel - represents progressing through internal structures to show next level state
     */
    int nextLevel() override;

private:

    /**
     * @brief Reads in the animal names and facts
     * @param file - holding all the information
     */
    void readInAnimals(QFile file);

    /**
     * @brief Reads in the animal ranks and
     * @param file - holding all the information
     */
    void readInAnimalRanks(QFile file);

    /**
     * @brief Chooses 2 random animals to be left and right
     */\
    void chooseMatchUp();

    /**
     * @brief Determines the winner based of ranks of the two animals
     */
    void findWinner();

    /**
     * @brief A list of pointers to all the animals
     */
    QList<Animal*> animalList;

    /**
     * @brief a map to all animal names and ranks
     */
    std::unordered_map<QString,float> animalRanks;

    /**
     * @brief A pointer to the currentWinner between the two animals
     */
    const Animal* currentWinner;

    /**
     * @brief String to ensure there is no dangling pointer
     */
    QString buildStr;

    /**
     * @brief Creates the first ad lib for the justification
     */
    void createAdLibOne();
    \
    /**
     * @brief Creates the second ad lib for the justification
     */
    void createAdLibTwo();

    /**
     * @brief Creates the three ad lib for the justification
     */
    void createAdLibThree();

    /**
     * @brief Changes the current justification to a different ad lib
     */
    void editCurrentJustification();

    /**
     * @brief Generates a random number
     */
    std::random_device randomIntGenerator;
};

#endif // RANDOMIZEGAMEMODE_H
