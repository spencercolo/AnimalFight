#include "animal.h"
#include <QDebug>

/**
 * Implementation of the animal class
 * @author John Radford
 * @author Marissa Kline
 * @version April 21, 2025
 *
 * Reviewed by Spencer Cologna
 */

Animal::Animal(const QString& name,
               const QString& height, const QString& weight,
               const QVector<QString>& strengths,
               const QString& weaknesses)
    :name(name), height(height), weight(weight),
    strengths(strengths), weaknesses(weaknesses)
{
    QString lowerName = name.toLower();
    lowerName = lowerName.replace(" ","");
    QString pathToAnimalPNG = ":/animals/" + lowerName + ".png";
    image = QPixmap(pathToAnimalPNG);
}

const QString& Animal::getName() const
{
    return name;
}

const QString& Animal::getHeight() const
{
    return height;
}

const QString& Animal::getWeight() const
{
    return weight;
}

const QVector<QString>& Animal::getStrengths() const
{
    return strengths;
}

const QString& Animal::getWeaknesses() const
{
    return weaknesses;
}

const QPixmap& Animal::getImage() const
{
    return image;
}
