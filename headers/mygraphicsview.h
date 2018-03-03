#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget* parent = 0);
protected:
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // MYGRAPHICSVIEW_H
