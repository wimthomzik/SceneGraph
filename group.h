#ifndef GROUP_H
#define GROUP_H

#include "node.h"
#include <vector>

class Group : public Node
{
public:
    using Node::Node;

    NodeType type() const override;
    void    addChild(NodeUPtr newChild);
    void    accept(NodeVisitor &v) override;
    void    removeChild(Node *child2Remove);
    void    draw(QPainter &p) const override;
    void    computeBounding() const override;
    Group*  asGroup() override { return this; }
    bool    isGroup() const override { return true; }
    const std::vector<NodeUPtr>&    children() const { return m_children; }

protected:
    std::vector<NodeUPtr> m_children;
};

#endif // GROUP_H
