#ifndef BUDGET_TABLEWITHFROZENCOLUMN_H
#define BUDGET_TABLEWITHFROZENCOLUMN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDate>

class TableWithFrozenColumn : public QWidget {
Q_OBJECT
public:
    explicit TableWithFrozenColumn(QWidget *parent = nullptr);

    void adjustFrozenColumnAndMonthDataTable();

    void setTableByMonth(int year, int month);

    void addSum();

    ~TableWithFrozenColumn() override;

public slots:

    void setFrozenColumnWidth(int logicalIndex, int oldSize, int newSize);

    void selectFrozenColumnCell(int row, int column);

    void selectMonthDataTableCell(int row, int column);

private:
    QHBoxLayout *fullTableLayout;
    QTableWidget *frozenColumn;
    QTableWidget *monthDataTable;
};


#endif //BUDGET_TABLEWITHFROZENCOLUMN_H
