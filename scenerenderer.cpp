#include "scenerenderer.h"

void SceneRenderer::renderScene(QPainter &p, Node *root, const QTransform &viewTransform, const QRectF& screenRect, Node* selected)
{
    if (!root) return;

    m_cullVisitor.cull(root, viewTransform.mapRect(screenRect));

    for (const auto& obj : m_cullVisitor.visibleObjects())
    {
        p.save();
        if (obj.node == selected)
        {
            p.setPen(Qt::red);
        }
        QPen pen = p.pen();
        pen.setCosmetic(true);
        p.setPen(pen);
        p.setTransform(obj.worldTransform, true);
        obj.node->draw(p);
        p.restore();
    }
    m_bbdVisitor.setPickedNode(selected);
    m_bbdVisitor.drawBoxes(root, &p);
}
