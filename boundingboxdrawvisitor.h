#ifndef BOUNDINGBOXVISITOR_H
#define BOUNDINGBOXVISITOR_H

#include "nodevisitor.h"
#include <QPainter>

class BoundingBoxDrawVisitor : public NodeVisitor
{
public:
    void drawBoxes(Node* root, QPainter* painter);
    void visit(Transform &) override;
    void visit(Group &) override;
    void visit(Circle &) override;
    void visit(Polygon &) override;
    void setPainter(QPainter *painter) { m_painter = painter; }
    void setPickedNode(const Node *pickedNode) { m_pickedNode = pickedNode; }

private:
    QPainter*   m_painter       = nullptr;
    const Node* m_pickedNode    = nullptr;
};

#endif // BOUNDINGBOXVISITOR_H
