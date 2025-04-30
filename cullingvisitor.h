#ifndef CULLINGVISITOR_H
#define CULLINGVISITOR_H

#include "nodevisitor.h"
#include "node.h"
#include <QRectF>
#include <vector>

struct VisibleObject {
    const Node* node;
    QTransform worldTransform;
};

class CullingVisitor : public NodeVisitor
{
public:
    void cull(Node *root, const QRectF &m_viewport);
    void visit(Group &group) override;
    void visit(Transform &transform) override;
    void visit(Circle &circle) override;
    void visit(Polygon &polygon) override;
    const std::vector<VisibleObject>& visibleObjects() const { return m_visibleObjects; }
    void setViewport(const QRectF &viewport) { m_viewport = viewport; }

private:
    QRectF                          m_viewport;
    std::vector<VisibleObject>      m_visibleObjects;
    QTransform                      m_currTrans;
};

#endif // CULLINGVISITOR_H
