#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTableWidget>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonLoadImage_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;

    void createTable(QTableWidget* table, int numOfRows, int numOfCols, const QVector<QString>& horizHeaders);

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    void fillTable(QTableWidget* table, const std::initializer_list<std::vector<T> > colsData,
                   const std::vector<int>& someToInt = {});
};

#endif // MAINWINDOW_H
