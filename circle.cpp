#include "circle.h"
#include "nodevisitor.h"
#include <QDebug>

void Circle::draw(QPainter &p) const
{
    p.drawEllipse(bounding());
}

void Circle::accept(NodeVisitor &v)
{
    v.visit(*this);
}

void Circle::computeBounding() const
{
    m_bounding = {-m_radius, -m_radius, m_radius * 2, m_radius * 2};
}

NodeType Circle::type() const
{
    return NodeType::Circle;
}
