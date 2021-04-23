#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    monthTable = new QTableWidget();
    today = QDate::currentDate();
    setWidgetToMonth(today.year(), today.month());
    setCentralWidget(monthTable);
}

void MainWindow::setWidgetToMonth(int year, int month) {
    QDate dateToWork(year, month, 1);
    monthTable = new QTableWidget(2, dateToWork.daysInMonth() + 2);
    // setting last column starting values and not editable
    for (int i = 0; i < monthTable->rowCount(); i++) {
        monthTable->setItem(i, monthTable->columnCount() - 1, new QTableWidgetItem("0"));
        monthTable->item(i, monthTable->columnCount() - 1)->setFlags(
                monthTable->item(i, monthTable->columnCount() - 1)->flags() ^ Qt::ItemIsEditable);
    }
    // inserting last sum row, starting values and not editable
    monthTable->insertRow(monthTable->rowCount());
    monthTable->setItem(monthTable->rowCount() - 1, 0, new QTableWidgetItem(tr("Sum")));
    monthTable->item(monthTable->rowCount() - 1, 0)->setFlags(
            monthTable->item(monthTable->rowCount() - 1, 0)->flags() ^ Qt::ItemIsEditable);
    for (int i = 1; i < monthTable->columnCount(); i++) {
        monthTable->setItem(monthTable->rowCount() - 1, i, new QTableWidgetItem("0"));
        monthTable->item(monthTable->rowCount() - 1, i)->setFlags(
                monthTable->item(monthTable->rowCount() - 1, i)->flags() ^ Qt::ItemIsEditable);
    }
    // setting horizontal header labels
    QStringList horizontalHeaderLabels;
    horizontalHeaderLabels.push_back(tr("Categories"));
    for (int i = 1; i <= dateToWork.daysInMonth(); i++) {
        horizontalHeaderLabels.push_back(QString::number(i));
    }
    horizontalHeaderLabels.push_back(tr("Sum"));
    monthTable->setHorizontalHeaderLabels(horizontalHeaderLabels);
    // hide vertical header
    monthTable->verticalHeader()->setVisible(false);
    // resize columns on full screen
    monthTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // set categories and sum columns fit to content
    monthTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    monthTable->horizontalHeader()->setSectionResizeMode(monthTable->columnCount() - 1,
                                                         QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow() {
    delete monthTable;
}
