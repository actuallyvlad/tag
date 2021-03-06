#include "mygraphicsview.h"
#include <QtMath>

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
}

/* wheelEvent snippet is taken from
 * https://stackoverflow.com/a/44422044 (author: cmaughan) */
void MyGraphicsView::wheelEvent(QWheelEvent* pWheelEvent)
{
    // Do a wheel-based zoom about the cursor position
    double angle = pWheelEvent->angleDelta().y();
    double factor = qPow(1.0015, angle);

    auto targetViewportPos = pWheelEvent->pos();
    auto targetScenePos = mapToScene(pWheelEvent->pos());

    scale(factor, factor);
    centerOn(targetScenePos);
    QPointF deltaViewportPos = targetViewportPos - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
    centerOn(mapToScene(viewportCenter.toPoint()));

    return;
}


