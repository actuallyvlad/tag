#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/algorithm.h"
#include <QFileDialog>
#include <QWheelEvent>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsViewMain->setDragMode(QGraphicsView::ScrollHandDrag);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable(QTableWidget* table, int numOfRows, int numOfCols, const QVector<QString>& horizHeaders) {
    table->setRowCount(numOfRows);
    table->setColumnCount(numOfCols);

    for (int i = 0; i < numOfCols; ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

        if (!horizHeaders.empty() && i < horizHeaders.size()) {
            table->setHorizontalHeaderItem(i, new QTableWidgetItem(horizHeaders[i]));
        }
    }

    table->verticalHeader()->hide();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// Only works for numeric types
// Table can only be filled with data of __the same__ type

template<typename T, typename>
void MainWindow::fillTable(QTableWidget* table, const std::initializer_list<vector<T>> colsData, const vector<int>& someToInt) {
    int colIndex = 0;

    for (auto col : colsData) {
        for (int i = 0; i < (int) col.size() && i < table->rowCount(); ++i) {
            if (!someToInt.empty()) {
                auto some = std::find(someToInt.begin(), someToInt.end(), colIndex);
                if (some != someToInt.end()) {
                    table->setItem(i, colIndex, new QTableWidgetItem(QString::number(int(col[i]))));
                }
                else {
                    table->setItem(i, colIndex, new QTableWidgetItem(QString::number(col[i])));
                }
            }
            else {
                table->setItem(i, colIndex, new QTableWidgetItem(QString::number(col[i])));
            }
        }

        ++colIndex;
    }
}

void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("Image Files (*.png *.jpg *.bmp *.gif *.tiff)")
                );

    QImage image(imagePath);

    int total;
    vector<double> indices;
    vector<double> lengths;
    vector<double> widths;
    vector<double> areas;

    image = FindGrains(imagePath, total, lengths, widths, areas);

    for (int i = 1; i <= total; ++i) {
        indices.push_back(i);
    }

    ui->labelTotal->setText(QString("Total: ") + QString::number(indices.size()));

    QVector<QString> colNames = {"#", "Length (mm)", "Width (mm)", "Area (mm²)"};

    createTable(ui->tableWidgetProperties, indices.size(), colNames.size(), colNames);
    fillTable(ui->tableWidgetProperties, {indices, lengths, widths, areas}, {0});

    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    scene->addItem(item);
    ui->graphicsViewMain->setScene(scene);
    ui->graphicsViewMain->show();
}
