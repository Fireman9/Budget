#include <QApplication>
#include "TableWithFrozenColumn.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TableWithFrozenColumn table;
    table.setWindowState(Qt::WindowMaximized);
    table.show();
    return QApplication::exec();
}
