#ifndef PICKINGVISITOR_H
#define PICKINGVISITOR_H

#include "nodevisitor.h"
#include "node.h"
#include <QPoint>
#include <QTransform>

class PickingVisitor : public NodeVisitor
{
public:
    void    reset();
    void    visit(Group &) override;
    void    visit(Circle &) override;
    void    visit(Polygon &) override;
    void    visit(Transform &) override;
    Node*   pickedNode() const { return m_pickedNode; }
    void    pick(Node *root, const QPointF &clickedPoint);

private:
    bool    checkPick(Node &node, const QRectF &transformedBoundingBox);

    Node*       m_pickedNode        = nullptr;
    int         m_deepestLevel      = -1;
    int         m_currentLevel      = 0;
    QPointF     m_clickedPoint;
    QTransform  m_currTransform;
};

#endif // PICKINGVISITOR_H
