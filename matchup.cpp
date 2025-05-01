/**
 * Implementation of class Matchup
 * @author John Radford
 * @author Marissa Kline
 * @version April 21, 2025
 *
 * Reviewed by Marisa De Astis
 */

#include "Matchup.h"

Matchup::Matchup(const Animal& left, const Animal& right, const QString& justification, bool winner)
    : leftAnimal(left), rightAnimal(right), winnerJustification(justification), winner(winner) {}


const Animal* Matchup::getLeftAnimal() const
{
    return &leftAnimal;
}


const Animal* Matchup::getRightAnimal() const
{
    return &rightAnimal;
}

const QString* Matchup::getJustification() const
{
    return &winnerJustification;
}


bool Matchup::getWinner() const
{
    return winner;
}
