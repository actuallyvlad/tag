#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithm.h"
#include <QFileDialog>
#include <QWheelEvent>

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

void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );

    QImage image(imagePath);
    image = FindGrains(imagePath);

    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    scene->addItem(item);
    ui->graphicsViewMain->setScene(scene);
    ui->graphicsViewMain->show();
}
