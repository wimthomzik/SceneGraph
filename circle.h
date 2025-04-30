#ifndef CIRCLE_H
#define CIRCLE_H

#include "geode.h"

class Circle : public Geode
{
public:
    using Geode::Geode;

    void draw(QPainter &p) const override;
    void accept(NodeVisitor &v) override;
    void computeBounding() const override;
    NodeType type() const override;
    double radius() const { return m_radius; }
    void setRadius(double newRadius)
    {
        m_radius    = newRadius;
        m_dirty     = true;
    }

private:
    double m_radius;
};

#endif // CIRCLE_H
