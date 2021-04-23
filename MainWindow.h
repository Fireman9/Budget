#ifndef BUDGET_MAINWINDOW_H
#define BUDGET_MAINWINDOW_H


#include <QMainWindow>
#include <QDate>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setWidgetToMonth(int year, int month);

    ~MainWindow() override;

private:
    QTableWidget *monthTable;
    QDate today;
};


#endif //BUDGET_MAINWINDOW_H
