#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <QObject>
#include "Box2D/Box2D.h"
#include <QTimer>

/**
 * @brief The PhysicsEngine class - Controls the physics for the Animal Fight Game
 * @author Spencer Cologna
 * @version April 21, 2025
 *
 * Reviewed by Aidan Cooley
 */
class PhysicsEngine : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsEngine(QObject *parent = nullptr);
    ~PhysicsEngine();

public slots:

    /**
     * @brief startWorld
     * Begins the timer to simulate the two bodies colliding
     */
    void startWorld();

    /**
     * @brief setFixtures
     * @param winner true: left fixture density is higher; false: right fixture density is higher
     */
    void setFixtures(bool winner);

    /**
     * @brief cancelSimulation - Cancels the set up of the Box2D bodies when returning to the main menu or resetting the game
     */
    void cancelSimulation();


private slots:

    /**
     * @brief worldStep
     * Performs a world step
     */
    void worldStep();

    /**
     * @brief stopWorld
     * Ends the timer to stop simulating the two bodies colliding
     */
    void stopWorld();


signals:

    /**
     * @brief sendLeftX
     * @param leftX x-coordinate of the left body
     */
    void sendLeftX(int leftX);

    /**
     * @brief sendRightX
     * @param rightX x-coordinate of the right body
     */
    void sendRightX(int rightX);

    /**
     * @brief animationFinish - signals to View that the collision animation has finished
     */
    void animationFinish();

private:

    /**
     * @brief world - Box2D world that houses everything in the physics simulation
     */
    b2World* world;

    /**
     * @brief ground - Box2D body that acts as the ground
     */
    b2Body* ground;

    /**
     * @brief leftBody - Box2D body that acts as the left body
     */
    b2Body* leftBody;

    /**
     * @brief rightBody - Box2D body that acts as the right body
     */
    b2Body* rightBody;

    /**
     * @brief box - Box2D Polygon shape for setting the shape of the left and right body
     */
    b2PolygonShape* box;

    /**
     * @brief timer - QTimer for controlling the rate of worldstep and for signalling that the simulation should stop
     */
    QTimer* timer;

    /**
     * @brief bodyFixture - Box2D Fixture Definiton for setting properties of the left and right bodies
     */
    b2FixtureDef* bodyFixture;

    /**
     * @brief prepareBodies
     * Creates the left and right bodies to be placed into the world
     */
    void prepareBodies();

    /**
     * @brief resetWorld
     * Destroys the left and right bodies in the world then call prepareWorld
     */
    void resetWorld();

};

#endif // PHYSICSENGINE_H
