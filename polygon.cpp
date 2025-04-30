#include "polygon.h"
#include "nodevisitor.h"

void Polygon::draw(QPainter &p) const
{
    p.drawPolygon(m_polygon);
}

void Polygon::computeBounding() const
{
    m_bounding = m_polygon.boundingRect();
}

void Polygon::accept(NodeVisitor &v)
{
    v.visit(*this);
}

NodeType Polygon::type() const
{
    return NodeType::Polygon;
}
