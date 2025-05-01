#ifndef ANIMAL_H
#define ANIMAL_H

#include <QObject>
#include <QPixmap>

/**
 * @brief The Animal class - Used to create an instance of an Animal object.
 * @author John Radford and Marissa Kline
 * @version March 11, 2025
 *
 * Reviewed by Spencer Cologna
 */
class Animal
{
public:

    /**
     * @brief Animal - Constructs a custom Animal object.
     * @param name - The name of the animal.
     * @param height - The height of the animal.
     * @param weight - The weight of the animal.
     * @param strengths - The strengths of the animal. Limited to a maximum of three facts.
     * @param weaknesses - The weaknesses of the animal. Limited to a maximum of three facts.
     */
    Animal(const QString& name, const QString& height, const QString& weight, const QVector<QString>& strengths, const QString& weaknesses);

    /**
     * @brief getName - Retrieves the name of the animal.
     * @return The animal's name.
     */
    const QString& getName() const;

    /**
     * @brief getHeight - Retrieves the height of the animal.
     * @return The animal's height.
     */
    const QString& getHeight() const;

    /**
     * @brief getWeight - Retrieves the weight of the animal.
     * @return The animal's weight.
     */
    const QString& getWeight() const;

    /**
     * @brief getStrengths - Retrieves the strengths of the animal.
     * @return The animal's strengths.
     */
    const QVector<QString>& getStrengths() const;

    /**
     * @brief getWeaknesses - Retrieves the weaknesses of the animal.
     * @return The animal's weaknesses.
     */
    const QString& getWeaknesses() const;

    /**
     * @brief getWeaknesses - Retrieves the weaknesses of the animal.
     * @return The animal's weaknesses.
     */
    const QPixmap& getImage() const;

private:

    /**
     * @brief name - The name of the animal.
     */
    QString name;

    /**
     * @brief height - The height of the animal.
     */
    QString height;

    /**
     * @brief weight - The weight of the animal.
     */
    QString weight;

    /**
     * @brief strengths - The strengths of the animal. Limited to a maximum of three facts.
     */
    QVector<QString> strengths;

    /**
     * @brief weaknesses - The weaknesses of the animal. Limited to a maximum of three facts.
     */
    QString weaknesses;

    /**
     * @brief image - The image of this animal
     */
    QPixmap image;
};

#endif // ANIMAL_H
