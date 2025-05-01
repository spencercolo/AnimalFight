#ifndef MATCHUP_H
#define MATCHUP_H

#include "animal.h"
#include <QString>

/**
 * @brief Matchup - represents a single animal matchup, including both opponents and a justification.
 * @author John Radford
 * @author Marissa Kline
 * @version April 21, 2025
 *
 * Reviewed by Marisa De Astis
 */
class Matchup {
public:

    /**
     * @brief Matchup - constructs a matchup with two animals and a justification.
     * @param left - the animal on the left side.
     * @param right - the animal on the right side.
     * @param justification - explanation for the outcome of the matchup.
     * @param winner - the winner of the current matchup, true if left, false if right.
     */
    Matchup(const Animal& left, const Animal& right, const QString& justification, bool winner);

    /**
     * @brief Matchup - default constructor.
     */
    Matchup();

    /**
     * @brief getLeftAnimal - retrieves the left-side animal in the matchup.
     * @return the left Animal.
     */
    const Animal* getLeftAnimal() const;

    /**
     * @brief getRightAnimal - retrieves the right-side animal in the matchup.
     * @return the right Animal.
     */
    const Animal* getRightAnimal() const;

    /**
     * @brief getJustification - returns the justification for the outcome of the matchup.
     * @return a string explaining the winner.
     */
    const QString* getJustification() const;

    /**
     * @brief getWinner - gets the int representing the winner
     * @return true if left, false if right.
     */
    bool getWinner() const;

private:

    /**
     * @brief leftAnimal - the animal on the left side of the matchup.
     */
    Animal leftAnimal;

    /**
     * @brief rightAnimal - the animal on the right side of the matchup.
     */
    Animal rightAnimal;

    /**
     * @brief winnerJustification - justification for which animal won the matchup.
     */
    QString winnerJustification;

    /**
     * @brief winner - the winner of the current matchup, true if left, false if right.
     */
    bool winner;
};

#endif // MATCHUP_H
