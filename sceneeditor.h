#ifndef SCENEEDITOR_H
#define SCENEEDITOR_H

#include <QMenu>
#include "node.h"

class Canvas;

class SceneEditor
{
public:
    explicit SceneEditor(Canvas* parentWidget = nullptr);
    void    handleRightClick(Node* selectedNode, const QPointF& scenePos, const QPoint& screenPos);

private:
    void        deleteNode();
    void        changeRadius();
    void        changePosition();
    void        propagateChangeUp(Node *node);
    QTransform  computeWorldTransform(Node *node);
    void        buildContextMenu(QMenu &menu, Node *selectedNode);
    Node*       addGeode(Node *node, const QPointF &sceneMousePos, NodeType type);
    void        handleMenuAction(const QString &action, Node *node, const QPointF &clickScenePos);

    Canvas* m_canvas = nullptr;
};

#endif // SCENEEDITOR_H
