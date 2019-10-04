#include "navigatorview.h"

#include "graphicsview.h"

#include <QMouseEvent>
#include <QDebug>

NavigatorView::NavigatorView(QWidget *parent)
    : QGraphicsView (parent)
    , m_viewportRegion(this->rect())
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color: rgba(0, 0, 0, 220);"
                  "border-radius: 3px;");
}

// doesn't take or manage its ownership
void NavigatorView::setMainView(GraphicsView *mainView)
{
    m_mainView = mainView;
}

void NavigatorView::updateMainViewportRegion()
{
    if (m_mainView != nullptr) {
        m_viewportRegion = mapFromScene(m_mainView->mapToScene(m_mainView->rect()));
        qDebug() << m_mainView->rect() << m_mainView->mapToScene(m_mainView->rect()) << m_viewportRegion;
    }
}

void NavigatorView::wheelEvent(QWheelEvent *event)
{
    event->ignore();
    return QGraphicsView::wheelEvent(event);
}

void NavigatorView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());
    painter.setPen(QPen(Qt::gray, 2));
    painter.drawRect(m_viewportRegion.boundingRect());
}