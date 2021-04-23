#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowState(Qt::WindowMaximized);
    mainWindow.show();
    return QApplication::exec();
}
