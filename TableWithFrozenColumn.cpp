#include "TableWithFrozenColumn.h"

TableWithFrozenColumn::TableWithFrozenColumn(QWidget *parent) : QWidget(parent) {
    fullTableLayout = new QHBoxLayout();
    frozenColumn = new QTableWidget(1, 1);
    monthDataTable = new QTableWidget();
    QDate today = QDate::currentDate();
    setTableByMonth(today.year(), today.month());
    adjustFrozenColumnAndMonthDataTable();
    addSum();
    fullTableLayout->addWidget(frozenColumn);
    fullTableLayout->addWidget(monthDataTable);
    this->setLayout(fullTableLayout);
}

void TableWithFrozenColumn::adjustFrozenColumnAndMonthDataTable() {
    fullTableLayout->setSpacing(0);
    frozenColumn->setStyleSheet("border: none;");
    monthDataTable->setStyleSheet("border: none;");
    // frozen column auto resizable
    connect(frozenColumn->horizontalHeader(), &QHeaderView::sectionResized, this,
            &TableWithFrozenColumn::setFrozenColumnWidth);
    frozenColumn->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    // disable possibility to resize row height
    frozenColumn->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // setting header name
    frozenColumn->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Categories")));
    // auto monthDataTable width adjustment
    monthDataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // disable vertical header
    monthDataTable->verticalHeader()->setVisible(false);
    // deselecting on frozenColumn or monthDataTable click
    connect(frozenColumn, &QTableWidget::cellClicked, this,
            &TableWithFrozenColumn::deselectFrozenColumn);
    connect(monthDataTable, &QTableWidget::cellClicked, this,
            &TableWithFrozenColumn::deselectMonthDataTable);
    connect(frozenColumn->horizontalHeader(), &QHeaderView::sectionClicked, this,
            &TableWithFrozenColumn::deselectFrozenColumn);
    connect(monthDataTable->horizontalHeader(), &QHeaderView::sectionClicked, this,
            &TableWithFrozenColumn::deselectMonthDataTable);
    // select whole row
    connect(frozenColumn->verticalHeader(), &QHeaderView::sectionClicked, this,
            &TableWithFrozenColumn::selectRow);
    // TODO: Multiple selection(Ctrl+Click)
}

void TableWithFrozenColumn::setTableByMonth(int year, int month) {
    QDate dateToWork(year, month, 1);
    monthDataTable = new QTableWidget(1, dateToWork.daysInMonth());
    // setting horizontal header labels
    QStringList horizontalHeaderLabels;
    for (int i = 1; i <= dateToWork.daysInMonth(); i++) {
        horizontalHeaderLabels.push_back(QString::number(i));
    }
    monthDataTable->setHorizontalHeaderLabels(horizontalHeaderLabels);
}

void TableWithFrozenColumn::addSum() {
    // inserting new sum row
    frozenColumn->insertRow(frozenColumn->rowCount());
    frozenColumn->setItem(frozenColumn->rowCount() - 1, 0, new QTableWidgetItem(tr("Sum")));
    // setting sum row not editable
    frozenColumn->item(frozenColumn->rowCount() - 1, 0)->setFlags(
            frozenColumn->item(frozenColumn->rowCount() - 1, 0)->flags() ^ Qt::ItemIsEditable);
    // inserting sum column and starting values, making them not editable
    monthDataTable->insertColumn(monthDataTable->columnCount());
    for (int i = 0; i < monthDataTable->rowCount(); i++) {
        monthDataTable->setItem(i, monthDataTable->columnCount() - 1, new QTableWidgetItem("0"));
        monthDataTable->item(i, monthDataTable->columnCount() - 1)->setFlags(
                monthDataTable->item(i, monthDataTable->columnCount() - 1)->flags() ^ Qt::ItemIsEditable);
    }
    // setting header name and making sum column auto resizable
    monthDataTable->setHorizontalHeaderItem(monthDataTable->columnCount() - 1, new QTableWidgetItem(tr("Sum")));
    monthDataTable->horizontalHeader()->setSectionResizeMode(monthDataTable->columnCount() - 1,
                                                             QHeaderView::ResizeToContents);
    // inserting last sum row and starting values, making them not editable
    monthDataTable->insertRow(monthDataTable->rowCount());
    for (int i = 0; i < monthDataTable->columnCount(); i++) {
        monthDataTable->setItem(monthDataTable->rowCount() - 1, i, new QTableWidgetItem("0"));
        monthDataTable->item(monthDataTable->rowCount() - 1, i)->setFlags(
                monthDataTable->item(monthDataTable->rowCount() - 1, i)->flags() ^ Qt::ItemIsEditable);
    }
}

void TableWithFrozenColumn::setFrozenColumnWidth(int logicalIndex, int oldSize, int newSize) {
    frozenColumn->setFixedWidth(newSize + 13);
}

void TableWithFrozenColumn::deselectFrozenColumn() {
    monthDataTable->clearSelection();
}

void TableWithFrozenColumn::deselectMonthDataTable() {
    frozenColumn->clearSelection();
}

void TableWithFrozenColumn::selectRow(int index) {
    monthDataTable->selectRow(index);
}

TableWithFrozenColumn::~TableWithFrozenColumn() {
    delete fullTableLayout;
    delete frozenColumn;
    delete monthDataTable;
}
