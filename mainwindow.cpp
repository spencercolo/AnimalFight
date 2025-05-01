#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

/**
 * Implementation of class MainWindow
 * @author Spencer Cologna
 * @author Sophia Hoermann
 * @author Marisa De Astis
 * @author Aidan Cooley
 * @version Apr 22, 2025
 *
 * Reveiwed by Sophia Hoermann
 */

MainWindow::MainWindow(AnimalGameModel *model, PhysicsEngine *physics, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->matchMenu->hide();
    ui->resultMenu->hide();
    ui->endMenu->hide();

    ui->restartResult->setEnabled(true);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(200, 170, 1020, 295);
    ui->matchPreview->setScene(scene);

    QApplication::setStyle("Fusion");

    /*-------------Connections from PhysicsModel to View----------*/
    connect(physics,
            &PhysicsEngine::sendLeftX,
            this,
            &MainWindow::receiveLeftX);

    connect(physics,
            &PhysicsEngine::sendRightX,
            this,
            &MainWindow::receiveRightX);

    connect(physics,
            &PhysicsEngine::animationFinish,
            this,
            &MainWindow::switchToResultMenu);

    /*-------------Connections from View to PhysicsModel------------*/
    connect(ui->submitButton,
            &QPushButton::clicked,
            physics,
            &PhysicsEngine::startWorld);

    //The following 6 connections are for resetting box2D in the event the player returns to the main menu/resets the game

    connect(ui->returnToMainMatch,
            &QPushButton::clicked,
            physics,
            &PhysicsEngine::cancelSimulation);

    connect(ui->returnToMainResult,
            &QPushButton::clicked,
            physics,
            &PhysicsEngine::cancelSimulation);

    connect(ui->returnToMainEnd,
            &QPushButton::clicked,
            physics,
            &PhysicsEngine::cancelSimulation);

    connect(ui->restartMatch,
            &QPushButton::clicked,
            physics,
            &PhysicsEngine::cancelSimulation);

    connect(ui->restartResult,
            &QPushButton::clicked,
            physics,
            &PhysicsEngine::cancelSimulation);

    /*-------------Connections from GameModel to PhysicsModel-------*/
    connect(model,
            &AnimalGameModel::provideWinner,
            physics,
            &PhysicsEngine::setFixtures);

    /*-------------Connections from View to View--------------------*/

    connect(ui->leftAnimalSelection,
            &QAbstractButton::clicked,
            this,
            &MainWindow::leftChecked);

    connect(ui->rightAnimalSelection,
            &QAbstractButton::clicked,
            this,
            &MainWindow::rightChecked);

    connect(ui->classicButton,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToMatchMenu);

    connect(ui->classicButton,
            &QPushButton::clicked,
            this,
            &MainWindow::resetAll);

    connect(ui->randomButton,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToMatchMenu);

    connect(ui->randomButton,
            &QPushButton::clicked,
            this,
            &MainWindow::resetAll);

    connect(ui->nextLevel,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToMatchMenu);

    connect(ui->nextLevel,
            &QPushButton::clicked,
            this,
            &MainWindow::resetAll);

    connect(ui->submitButton,
            &QPushButton::clicked,
            this,
            &MainWindow::disableOnSubmit);

    connect(ui->nextLevel,
            &QPushButton::clicked,
            this,
            &MainWindow::enableMainMenuRestart);

    connect(ui->returnToMainMatch,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToMainMenu);

    connect(ui->returnToMainResult,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToMainMenu);

    connect(ui->returnToMainEnd,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToMainMenu);

    connect(ui->restartMatch,
            &QPushButton::clicked,
            this,
            &MainWindow::resetAll);

    connect(ui->restartResult,
            &QPushButton::clicked,
            this,
            &MainWindow::resetAll);

    connect(ui->restartResult,
            &QPushButton::clicked,
            this,
            &MainWindow::switchToMatchMenu);

    /*-------------Connections from View to Model--------------------*/

    connect(ui->classicButton,
            &QPushButton::clicked,
            model,
            &AnimalGameModel::startGamePreset);

    connect(ui->randomButton,
            &QPushButton::clicked,
            model,
            &AnimalGameModel::startGameRandom);

    connect(ui->nextLevel,
            &QPushButton::clicked,
            model,
            &AnimalGameModel::nextLevel);

    connect(ui->leftAnimalSelection,
            &QAbstractButton::clicked,
            model,
            &AnimalGameModel::clickedLeftAnimal);

    connect(ui->rightAnimalSelection,
            &QAbstractButton::clicked,
            model,
            &AnimalGameModel::clickedRightAnimal);

    connect(ui->submitButton,
            &QPushButton::clicked,
            model,
            &AnimalGameModel::finalWinnerSelected);

    connect(ui->restartMatch,
            &QPushButton::clicked,
            model,
            &AnimalGameModel::restartGame);

    connect(ui->restartResult,
            &QPushButton::clicked,
            model,
            &AnimalGameModel::restartGame);

    /*-------------Connections from Model to View--------------------*/
    connect(model,
            &AnimalGameModel::provideLeftAnimal,
            this,
            &MainWindow::receiveLeftAnimal);

    connect(model,
            &AnimalGameModel::provideRightAnimal,
            this,
            &MainWindow::receiveRightAnimal);

    connect(model,
            &AnimalGameModel::provideJustification,
            this,
            &MainWindow::receiveJustification);

    connect(model,
            &AnimalGameModel::endGameStats,
            this,
            &MainWindow::receiveEndGameStats);

    connect(model,
            &AnimalGameModel::provideLevel,
            this,
            &MainWindow::receiveLevel);

    connect(model,
            &AnimalGameModel::userCorrect,
            this,
            &MainWindow::receiveUserCorrect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToMatchMenu()
{
    ui->resultMenu->hide();
    ui->resultMenu->setDisabled(true);
    ui->mainMenu->hide();
    ui->mainMenu->setDisabled(true);
    ui->matchMenu->show();
    ui->matchMenu->setEnabled(true);

    ui->returnToMainMatch->setEnabled(true);
    ui->restartMatch->setEnabled(true);
}

void MainWindow::switchToMainMenu()
{
    ui->resultMenu->hide();
    ui->resultMenu->setDisabled(true);
    ui->matchMenu->hide();
    ui->matchMenu->setDisabled(true);
    ui->endMenu->hide();
    ui->endMenu->setDisabled(true);
    ui->mainMenu->show();
    ui->mainMenu->setEnabled(true);
}

void MainWindow::switchToResultMenu()
{
    ui->matchMenu->hide();
    ui->matchMenu->setDisabled(true);
    ui->resultMenu->show();
    ui->resultMenu->setEnabled(true);

    //clean up QGraphicsScene for next images
    scene->clear();
}


void MainWindow::rightChecked()
{
    if (!ui->rightAnimalSelection->checkState())
    {
        ui->submitButton->setDisabled(true);
    }
    else
    {
        ui->submitButton->setEnabled(true);
    }

    ui->leftAnimalSelection->setChecked(false);
}

void MainWindow::leftChecked()
{
    if (!ui->leftAnimalSelection->checkState())
    {
        ui->submitButton->setDisabled(true);
    }
    else
    {
        ui->submitButton->setEnabled(true);
    }

    ui->rightAnimalSelection->setChecked(false);
}

void MainWindow::receiveLeftAnimal(const Animal *left)
{
    ui->leftAnimalName->setText(left->getName());

    QString statsLine = "Height: " + left->getHeight() + "\n" + "Weight: "
                        + left->getWeight() + "\n" + "Strengths:\n";
    foreach (QString strength, left->getStrengths())
    {
        statsLine.append(strength + "\n");
    }

    statsLine.append("Weakness: " + left->getWeaknesses());

    ui->leftAnimalStats->setText(statsLine);

    QPixmap leftPixmap = left->getImage();
    leftImage = scene->addPixmap(leftPixmap.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    leftImage->setPos(200, 185);
}

void MainWindow::receiveRightAnimal(const Animal *right)
{
    ui->rightAnimalName->setText(right->getName());

    QString statsLine = "Height: " + right->getHeight() + "\n" + "Weight: "
                        + right->getWeight() + "\n" + "Strengths: \n";
    foreach (QString strength, right->getStrengths())
    {
        statsLine.append(strength + "\n");
    }

    statsLine.append("Weakness: " + right->getWeaknesses());

    ui->rightAnimalStats->setText(statsLine);

    QPixmap rightPixmap = right->getImage();
    rightImage = scene->addPixmap(rightPixmap.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    rightImage->setPos(925, 185);
}

void MainWindow::receiveJustification(const QString *justification)
{
    ui->reasoningText->setText(*justification);
}

void MainWindow::receiveEndGameStats(int finalUserScore)
{
    QString score = QString::number(finalUserScore);
    ui->score->setText("You scored " + score + " out of 30");
    ui->resultMenu->hide();
    ui->resultMenu->setDisabled(true);
    ui->matchMenu->hide();
    ui->matchMenu->setDisabled(true);
    ui->endMenu->show();
    ui->endMenu->setEnabled(true);
}

void MainWindow::receiveLevel(int level)
{
    ui->levelCounterResult->setText("Level: " + QString::number(level));
    ui->levelCounterMatch->setText("Level: " + QString::number(level));
}

void MainWindow::resetAll()
{
    //submit button
    ui->submitButton->setDisabled(true);

    //checks
    ui->leftAnimalSelection->setChecked(false);
    ui->leftAnimalSelection->setEnabled(true);
    ui->rightAnimalSelection->setChecked(false);
    ui->rightAnimalSelection->setEnabled(true);

    scene->clear();
}

void MainWindow::receiveUserCorrect(bool correct)
{
    if(correct)
    {
        ui->rightOrWrong->setText("CORRECT!");
        ui->rightOrWrong->setStyleSheet("background-color: rgb(57, 183, 76);");

        QPixmap checkIcon(":/uiassets/checkIcon.png");
        ui->feedbackIcon->setScaledContents(true);
        ui->feedbackIcon->setPixmap(checkIcon);

        return;
    }

    ui->rightOrWrong->setText("WRONG!");
    ui->rightOrWrong->setStyleSheet("background-color: rgb(242, 59, 89);");

    QPixmap xIcon(":/uiassets/xicon.png");
    ui->feedbackIcon->setScaledContents(true);
    ui->feedbackIcon->setPixmap(xIcon);
}

void MainWindow::receiveLeftX(int leftX)
{
    leftImage->setPos(leftX, leftImage->pos().y());
}

void MainWindow::receiveRightX(int rightX)
{
    rightImage->setPos(rightX, rightImage->pos().y());
}

void MainWindow::disableOnSubmit()
{
    //submit button
    ui->submitButton->setDisabled(true);

    //checks
    ui->leftAnimalSelection->setDisabled(true);
    ui->rightAnimalSelection->setDisabled(true);

    //restart and main menu
    ui->returnToMainMatch->setDisabled(true);
    ui->restartMatch->setDisabled(true);
}

void MainWindow::enableMainMenuRestart()
{
    ui->returnToMainMatch->setEnabled(true);
    ui->restartMatch->setEnabled(true);
}
