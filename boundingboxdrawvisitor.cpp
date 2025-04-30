#include "boundingboxdrawvisitor.h"
#include "group.h"
#include "transform.h"
#include "polygon.h"
#include "circle.h"

void BoundingBoxDrawVisitor::drawBoxes(Node *root, QPainter *painter)
{
    setPainter(painter);
    root->accept(*this);
}

void BoundingBoxDrawVisitor::visit(Transform &transform)
{
    m_painter->save();
    m_painter->rotate(transform.rotationRadiant());
    m_painter->translate(transform.position().x(), transform.position().y());

    visit(static_cast<Group&>(transform));

    m_painter->restore();
}

void BoundingBoxDrawVisitor::visit(Group &group)
{
    if (&group == m_pickedNode)
    {
        m_painter->setPen(Qt::red);
    }
    QPen pen = m_painter->pen();
    pen.setCosmetic(true);
    m_painter->setPen(pen);
    m_painter->drawRect(group.bounding());
    pen = m_painter->pen();
    pen.setColor(Qt::black);
    m_painter->setPen(pen);

    for (auto &child : group.children())
    {
        child->accept(*this);
    }
}

void BoundingBoxDrawVisitor::visit(Circle &circle)
{
    m_painter->drawRect(circle.bounding());
}

void BoundingBoxDrawVisitor::visit(Polygon &polygon)
{
    m_painter->drawRect(polygon.bounding());
}
