#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "animal.h"
#include <QGraphicsScene>
#include "physicsengine.h"
#include "animalgamemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class, used as the View for displaying our Animal Game
 * @author Spencer Cologna
 * @author Aidan Cooley
 * @author Misa de Astis
 * @author Sophia Hoermann
 * @version April 21, 2025
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AnimalGameModel *model, PhysicsEngine *physics, QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    /**
     * @brief Switches the curret UI to be the match menu
     */
    void switchToMatchMenu();

    /**
     * @brief Switches the curret UI to be the main menu
     */
    void switchToMainMenu();

    /**
     * @brief Switches the curret UI to be the result menu
     */
    void switchToResultMenu();

    /**
     * @brief Slot when the left check box is clicked
     */
    void leftChecked();

    /**
     * @brief Slot when the right check box is clicked
     */
    void rightChecked();

    /**
     * @brief receives the left X coordinate from physics engine
     * @param leftX int - the left X coordinate
     */
    void receiveLeftX(int leftX);

    /**
     * @brief receive the right X coordinate from physics engine
     * @param rightX int - the right X coordinate
     */
    void receiveRightX(int rightX);

    /**
     * @brief Resets checkbox and submit buttons after a level
     */
    void resetAll();

    /**
     * @brief Receiving information about the left animal from the model
     * @param left Animal
     */
    void receiveLeftAnimal(const Animal *left);

    /**
     * @brief Receiving information about the right animal from the model
     * @param right Animal
     */
    void receiveRightAnimal(const Animal *right);

    /**
     * @brief Receiving justification for the winner of the match up
     * @param justification QString
     */
    void receiveJustification(const QString *justification);

    /**
     * @brief Receiving the final stats of the game, also indicates end of game
     * @param finalUserScore int
     */
    void receiveEndGameStats(int finalUserScore);

    /**
     * @brief Receives the current level the user is on to display
     * @param level int
     */
    void receiveLevel(int level);

    /**
     * @brief Receives the outcome of the user's guess after being checked
     * by the model
     * @param true if user guessed correctly, false otherwise
     */
    void receiveUserCorrect(bool correct);

    /**
     * @brief Disables the submit button, checks, restart, and main menu
     */
    void disableOnSubmit();

    /**
     * @brief Enables main menu and restart buttons
     */
    void enableMainMenuRestart();

signals:
    /**
     * @brief Signal saying that the left checkbox was clicked
     */
    void leftSelected();

    /**
     * @brief Signal saying that the right checkbox was clicked
     */
    void rightSelected();


private:

    /**
     * @brief A pointer to the UI
     */
    Ui::MainWindow *ui;

    /**
     * @brief The left animal picture in the game
     */
    QGraphicsPixmapItem* leftImage;

    /**
     * @brief The right animal picture in the game
     */
    QGraphicsPixmapItem* rightImage;

    /**
     * @brief The scene where the physics takes place
     */
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
