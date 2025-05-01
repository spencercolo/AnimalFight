#ifndef PRESETGAMEMODE_H
#define PRESETGAMEMODE_H

#include "gamemode.h"
#include "matchup.h"

/**
 * @brief The PresetGameMode class- controls the information setup for the Preset Matchups Game Mode; derived class of GameMode
 * @author John Radford
 * @author Marissa Kline
 * @version April 21, 2025
 *
 * Reviewed by Marisa De Astis
 */
class PresetGameMode : public GameMode
{
public:

    PresetGameMode();

    ~PresetGameMode() override;

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
      * @brief matchups - vector datastructure to hold each matchup and also represent level progression.
      */
    QVector<Matchup> matchups;

    /**
     * @brief generateMatchups - Helper method to fill the matchups backing structure.
     * @return All animal matchups and their winning justification.
     */
    void generateMatchups();

    /**
     * @brief convertToVector - Helper method to convert JSON array into a vector of strings.
     * @return The JSON array converted into a vector.
     */
    QVector<QString> convertToVector(const QJsonArray& jsonArray);

};

#endif // PRESETGAMEMODE_H
