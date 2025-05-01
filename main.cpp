/**
 * Class for holding the main method
 * @author Spencer Cologna
 * @author Aidan Cooley
 * @author Marissa Kline
 * @author Marisa Nieto
 * @author Sophia Hoermann
 * @author John Radford
 * @version April 21, 2025
 */

#include "mainwindow.h"
#include "physicsengine.h"
#include "animalgamemodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhysicsEngine *physics = new PhysicsEngine();
    AnimalGameModel *model = new AnimalGameModel();
    MainWindow w(model, physics);
    w.show();
    return a.exec();
}
