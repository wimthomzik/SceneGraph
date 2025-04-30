#ifndef POLYGON_H
#define POLYGON_H


#include <QPolygonF>
#include "geode.h"
#include "node.h"

class Polygon : public Geode
{
public:
    using Geode::Geode;

    NodeType            type() const override;
    void                accept(NodeVisitor &v) override;
    void                draw(QPainter &p) const override;
    void                computeBounding() const override;
    const QPolygonF&    polygon() const { return m_polygon; }
    void                setPolygon(const QPolygonF &newPoly) { m_polygon = newPoly; }

private:
    QPolygonF   m_polygon;
};

#endif // POLYGON_H
