#include "node.h"
#include "group.h"
#include <memory>

Node::Node(Group* parent) :
    m_parent(parent)
{

}

Node::~Node() = default;

void Node::setParent(Group *newParent)
{
    // Remove self from current parent if present
    if (hasParent())
    {
        m_parent->removeChild(this);
    }

    // Set new parent
    m_parent = newParent;
}

bool Node::hasParent()
{
    return m_parent != nullptr;
}

const QRectF &Node::bounding() const
{
    if (m_dirty)
    {
        computeBounding();
        m_dirty = false;
    }
    return m_bounding;
}
