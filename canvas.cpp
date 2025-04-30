#include "canvas.h"
#include <QPaintEvent>
#include <QDebug>
#include "cullingvisitor.h"
#include "geode.h"
#include "circle.h"
#include "polygon.h"
#include <QMenu>
#include <QInputDialog>

using Vec2 = wtm::Vec2T<double>;

/**
 * Further improvements: Camera-Abstraction with MapToScene, zoomAt,..
 */

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), m_pickVisitor(PickingVisitor()), m_sceneRenderer(SceneRenderer()), m_sceneEditor(SceneEditor(this))
{
    startTimer(100);
}

void Canvas::paintEvent(QPaintEvent *)
{
    // Set up painter
    QPainter    p(this);
    setPenSettings(&p);

    // Adjust and draw screenRect for visibility of culling effect
    QRectF  screenRect = adjustScreenRect();
    p.drawRect(viewTransform().mapRect(screenRect));

    m_sceneRenderer.renderScene(p, m_root.get(), viewTransform(), screenRect, pickedNode());
}


void Canvas::mousePressEvent(QMouseEvent *event)
{
    // Safe mousePos for calculating translating after dragging
    m_prevPosition = p2v(event->pos());

    QPointF scenePos = mapToScene(event->pos());

    m_pickVisitor.pick(m_root.get(), scenePos);
    if(event->button() == Qt::RightButton)
    {
        m_sceneEditor.handleRightClick(pickedNode(), scenePos, event->globalPos());
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        Vec2 v {p2v(event->pos())};
        m_offset        += v - m_prevPosition;
        m_prevPosition  = v;
        update();
    }
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    Vec2 mousePos       = p2v(event->pos());
    double scaleFactor  = (event->delta() > 0) ? 1.1 : 0.9;
    m_offset            = (mousePos - (mousePos - m_offset) * scaleFactor);
    m_scale             *= scaleFactor;
    update();
}

void Canvas::timerEvent(QTimerEvent *)
{
    update();
}

void Canvas::setRoot(TransformUPtr newRoot)
{
    m_root = std::move(newRoot);
}

QPointF Canvas::mapToScene(const QPointF &mousePos)
{
    QTransform viewTransform;
    viewTransform.scale(1. / m_scale.x(), -1. / m_scale.y());
    viewTransform.translate(-m_offset.x(), -m_offset.y());
    return viewTransform.map(QPointF(mousePos));
}

void Canvas::setPenSettings(QPainter* p) const
{
    QPen pen = p->pen();
    pen.setCosmetic(true);
    p->setPen(pen);
    p->translate(m_offset.x(), m_offset.y());
    p->scale(m_scale.x(), -m_scale.y());
}

QTransform Canvas::viewTransform() const
{
    QTransform t;
    t.scale(1. / m_scale.x(), -1. / m_scale.y());
    t.translate(-m_offset.x(), -m_offset.y());
    return t;
}

QRectF Canvas::adjustScreenRect()
{
    QRectF r = rect();
    r.adjust(r.width() * .25, r.height() * .25, -r.width() * .25, -r.height() * .25);
    return r;
}
