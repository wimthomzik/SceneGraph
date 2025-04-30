#ifndef NODEVISITOR_H
#define NODEVISITOR_H

class Node;
class Geode;
class Group;
class Transform;
class Circle;
class Polygon;

class NodeVisitor
{
public:
    NodeVisitor() = default;
    virtual ~NodeVisitor();

    virtual void visit(Node &) {}
    virtual void visit(Geode &) {}
    virtual void visit(Group &) {}
    virtual void visit(Transform &) {}
    virtual void visit(Circle &) {}
    virtual void visit(Polygon &) {}
};

#endif // NODEVISITOR_H
