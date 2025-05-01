#include "physicsengine.h"

/**
 * Implementation of the Physics Engine class used for simulating collisions
 * @author Spencer Cologna
 * @version 4/21/2025
 *
 * Reviewed By Aidan Cooley
 */
PhysicsEngine::PhysicsEngine(QObject *parent)
    : QObject{parent},
    world(new b2World(b2Vec2(0.0f, -10.0f))),
    timer(new QTimer())
{
    //First connect a timer to the world step
    connect(timer, &QTimer::timeout, this, &PhysicsEngine::worldStep);

    //Create the ground
    b2BodyDef groundDef;
    groundDef.position.Set(0.0f, -10.0f);

    ground = world->CreateBody(&groundDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(1000.0f, 10.0f);

    ground->CreateFixture(&groundBox, 0.0f);

    //Create the body's definition, this will be "shared" between left and right bodies
    prepareBodies();
}

void PhysicsEngine::prepareBodies()
{
    b2BodyDef leftBodyDef;
    leftBodyDef.type = b2_dynamicBody;
    leftBodyDef.position.Set(200.0f, -10.0f);

    b2BodyDef rightBodyDef;
    rightBodyDef.type = b2_dynamicBody;
    rightBodyDef.position.Set(925.0f, -10.0f);

    //make the left and right bodies
    leftBody = world->CreateBody(&leftBodyDef);

    rightBody = world->CreateBody(&rightBodyDef);

    //setup the body's fixture defintion, it will be modified later
    box = new b2PolygonShape;
    box->SetAsBox(150.0f, 10.0f);

    bodyFixture = new b2FixtureDef;
    bodyFixture->shape = box;
}

void PhysicsEngine::setFixtures(bool winner)
{
    if(winner)
    {
        bodyFixture->density = 5.0f;
        bodyFixture->friction = 1.0f;
        bodyFixture->restitution = 0.5f;
        leftBody->CreateFixture(bodyFixture);
        leftBody->SetLinearVelocity(b2Vec2(800.0f, 0.0f));

        bodyFixture->density = 1.0f;
        bodyFixture->friction = 0.0f;
        bodyFixture->restitution = 1.0f;
        rightBody->CreateFixture(bodyFixture);
        rightBody->SetLinearVelocity(b2Vec2(-800.0f, 0.0f));
    }
    else
    {
        bodyFixture->density = 5.0f;
        bodyFixture->friction = 1.0f;
        bodyFixture->restitution = 0.5f;
        rightBody->CreateFixture(bodyFixture);
        rightBody->SetLinearVelocity(b2Vec2(-100.0f, 0.0f));

        bodyFixture->density = 1.0f;
        bodyFixture->friction = 0.0f;
        bodyFixture->restitution = 1.0f;
        leftBody->CreateFixture(bodyFixture);
        leftBody->SetLinearVelocity(b2Vec2(100.0f, 0.0f));
    }
}

void PhysicsEngine::startWorld()
{
    timer->start(5);
    QTimer::singleShot(3000, this, &PhysicsEngine::stopWorld);
}

void PhysicsEngine::worldStep()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 4;

    world->Step(timeStep, velocityIterations, positionIterations);

    emit sendLeftX(leftBody->GetPosition().x);
    emit sendRightX(rightBody->GetPosition().x);
}

void PhysicsEngine::stopWorld()
{
    timer->stop();
    resetWorld();
    emit animationFinish();
}

void PhysicsEngine::resetWorld()
{
    world->DestroyBody(leftBody);
    world->DestroyBody(rightBody);
    prepareBodies();
}

void PhysicsEngine::cancelSimulation()
{
    resetWorld();
}

PhysicsEngine::~PhysicsEngine()
{
    delete timer;
    delete world;
}
