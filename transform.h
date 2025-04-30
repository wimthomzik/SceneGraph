#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "group.h"


class Transform : public Group
{
public:
    Transform() = default;
    Transform(Group *parent, const QPointF &m_position, double m_rotationRadiant);


    NodeType        type() const override;
    void            accept(NodeVisitor &v) override;
    Transform*      asTransform() override {return this;}
    const QPointF&  position() const { return m_position; }
    bool            isTransform() const override {return true;}
    double          rotationRadiant() const { return m_rotationRadiant; }
    void            setPosition(const QPointF &newPos) { m_position = newPos; }
    void            setRotationRadiant(double newRotationRadiant) { m_rotationRadiant = newRotationRadiant; }

private:
    QPointF m_position {0, 0};
    double  m_rotationRadiant = 0.;
};

using TransformUPtr = std::unique_ptr<Transform>;

#endif // TRANSFORM_H
