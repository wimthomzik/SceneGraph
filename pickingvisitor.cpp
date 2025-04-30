#include "pickingvisitor.h"
#include "group.h"
#include "transform.h"
#include "polygon.h"
#include "circle.h"
#include <QDebug>

void PickingVisitor::pick(Node *root, const QPointF &clickedPoint)
{
    reset();
    if(!root) return;
    m_clickedPoint = clickedPoint;
    root->accept(*this);
}

void PickingVisitor::visit(Group &g)
{
    if (checkPick(g, m_currTransform.mapRect(g.bounding())))
    {
        m_currentLevel++;
        for (auto &child : g.children())
        {
            child->accept(*this);
        }
        m_currentLevel--;
    }

}

void PickingVisitor::visit(Transform &t)
{
    QTransform prevTransformation = m_currTransform;

    m_currTransform.rotateRadians(t.rotationRadiant());
    m_currTransform.translate(t.position().x(), t.position().y());

    PickingVisitor::visit(static_cast<Group &>(t));

    m_currTransform = prevTransformation;
}

void PickingVisitor::visit(Circle &c)
{
    checkPick(c, m_currTransform.mapRect(c.bounding()));
}

void PickingVisitor::visit(Polygon &p)
{
    checkPick(p, m_currTransform.mapRect(p.bounding()));
}

bool PickingVisitor::checkPick(Node& n, const QRectF &transformedBoundingBox)
{
    if (transformedBoundingBox.contains(m_clickedPoint))
    {
        if (m_currentLevel >= m_deepestLevel)
        {
            m_pickedNode = &n;
            m_deepestLevel = m_currentLevel;
        }
        return true;
    }
    return false;
}

void PickingVisitor::reset()
{
    m_pickedNode = nullptr;
    m_deepestLevel = -1;
    m_currentLevel = 0;
}
