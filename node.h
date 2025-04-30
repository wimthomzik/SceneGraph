#ifndef NODE_H
#define NODE_H

#include <QRectF>
#include <memory>
#include <QPainter>

class Group;
class Transform;
class NodeVisitor;

enum class NodeType
{
    Node,
    Group,
    Transform,
    Geode,
    Circle,
    Polygon
};

class Node
{
public:
    Node() = default;
    Node(Group* parent);
    virtual ~Node();

    bool                hasParent();
    const QRectF&       bounding() const;
    void                setParent(Group *newParent);
    void                setDirty() { m_dirty = true; }
    Group*              parent() const { return m_parent; }
    virtual void        accept(NodeVisitor &v) = 0;
    virtual void        draw(QPainter &p) const = 0;
    virtual Group*      asGroup() { return nullptr; }
    virtual bool        isGroup() const { return false; }
    virtual bool        isTransform() const { return false; }
    virtual Transform*  asTransform() { return nullptr; }
    virtual NodeType    type() const { return NodeType::Node; }

protected:
    virtual void    computeBounding() const = 0;

    mutable bool    m_dirty = true;
    mutable QRectF  m_bounding;
    Group*          m_parent = nullptr;
};

using NodeUPtr = std::unique_ptr<Node>;

#endif // NODE_H
