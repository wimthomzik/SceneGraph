#include "transform.h"
#include "nodevisitor.h"
#include <QtDebug>

Transform::Transform(Group *parent, const QPointF &position, double rotationRadiant) :
    Group (parent), m_position(position), m_rotationRadiant(rotationRadiant)
{

}

void Transform::accept(NodeVisitor &v)
{
    v.visit(*this);
}

NodeType Transform::type() const
{
    return NodeType::Transform;
}
