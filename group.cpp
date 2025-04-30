#include "group.h"
#include "nodevisitor.h"
#include <algorithm>
#include "transform.h"

void Group::draw(QPainter &p) const
{
    p.drawRect(bounding());
}

void Group::addChild(NodeUPtr newChild)
{
    m_children.push_back(std::move(newChild));
    m_children.back()->setParent(this);
}

void Group::removeChild(Node* child2Remove)
{
    m_children.erase(
                std::remove_if(m_children.begin(), m_children.end(),
                            [child2Remove](NodeUPtr &node) { return node.get() == child2Remove; }
                ), m_children.end());
}

void Group::computeBounding() const
{
    QRectF total;
    for (const auto &child : m_children)
    {
        QRectF childBounds = child->bounding();
        if (child->type() == NodeType::Transform)
        {
            auto* tChild = static_cast<Transform*>(child.get());
            QTransform local;
            local.rotateRadians(tChild->rotationRadiant());
            local.translate(tChild->position().x(), tChild->position().y());
            total |= local.mapRect(child->bounding());
        }
        else
        {
            total |= childBounds;
        }
    }
    m_bounding = total;
}

NodeType Group::type() const
{
    return NodeType::Group;
}

void Group::accept(NodeVisitor &v)
{
    v.visit(*this);
}
