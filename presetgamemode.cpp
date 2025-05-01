#include "presetgamemode.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

/**
 * Implementation of class PresetGameMode
 * @author John Radford
 * @author Marissa Kline
 * @version April 21, 2025
 *
 * Reviewed by Marisa De Astis
 */

PresetGameMode :: PresetGameMode()
{

    // Populate matchups vector with each matchup object
    generateMatchups();

    // Base class members -
    // Initialize each member variable in the gameMode base class to it's starting value

    currentLevel = 1;

    currentWinnerIsLeft = matchups[currentLevel - 1].getWinner();

    currentLeftOpponent = matchups[currentLevel - 1].getLeftAnimal();

    currentRightOpponent = matchups[currentLevel - 1].getRightAnimal();

    currentJustification = matchups[currentLevel - 1].getJustification();

};

PresetGameMode::~PresetGameMode()
{

}


int PresetGameMode::nextLevel()
{
    if(currentLevel >= (int) matchups.size())
    {
        return 1; // Reached or exceeded bounds
    }

    currentLevel++;

    // Update base class fields
    currentWinnerIsLeft = matchups[currentLevel - 1].getWinner();
    currentLeftOpponent = matchups[currentLevel - 1].getLeftAnimal();
    currentRightOpponent = matchups[currentLevel - 1].getRightAnimal();
    currentJustification = matchups[currentLevel - 1].getJustification();

    return 0; // Still within bounds
}

void PresetGameMode::generateMatchups()
{

    // Locate the JSON file, open it and read the information
    QFile file(":/textFiles/presetGameJSON.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Extract the raw text from the file then put it in JSON deserializer format
    QString rawText = file.readAll();
    file.close();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(rawText.toUtf8());

    // Establish QJsonDocument as an array, as multiple matchups will be made
    QJsonArray jsonArray = jsonDocument.array();

    // Iterate over all contents of the JSON array to make objects
    for(const QJsonValue& val : jsonArray)
    {

        //Extract the current object (represented by current index of array)
        QJsonObject currentObject = val.toObject();

        // Deserialize leftAnimal
        QJsonObject leftObj = currentObject["leftAnimal"].toObject();
        Animal left(
            leftObj["name"].toString(),
            leftObj["height"].toString(),
            leftObj["weight"].toString(),
            convertToVector(leftObj["strengths"].toArray()),
            leftObj["weaknesses"].toString()
            );

        // Deserialize rightAnimal
        QJsonObject rightObj = currentObject["rightAnimal"].toObject();
        Animal right(
            rightObj["name"].toString(),
            rightObj["height"].toString(),
            rightObj["weight"].toString(),
            convertToVector(rightObj["strengths"].toArray()),
            rightObj["weaknesses"].toString()
            );

        // Get justification and winner
        QString justification = currentObject["justification"].toString();
        bool winner = currentObject["winner"].toBool();

        // Build and add matchup object
        matchups.append(Matchup(left, right, justification, winner));
    }
}

QVector<QString> PresetGameMode::convertToVector(const QJsonArray& jsonArray)
{

    // Vector to hold return values
    QVector<QString> returnVector;

    // Fill the return vector with the JSON array strings
    for(const auto& currentObject : jsonArray)
        returnVector.append(currentObject.toString());

    return returnVector;
}
